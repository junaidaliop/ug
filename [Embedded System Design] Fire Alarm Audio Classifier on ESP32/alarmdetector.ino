#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/i2s.h"
#include "driver/gpio.h"
#include "EloquentTinyML.h"
#include "model_data.h"

#define AUDIO_SAMPLE_RATE 16000
#define AUDIO_VECTOR_SIZE 32

// Replace with your specific hardware pins
#define I2S_BCK_GPIO 25
#define I2S_WS_GPIO 26
#define I2S_DATA_GPIO 27
#define I2S_DOUT_GPIO 25
#define I2S_DIN_GPIO 26
#define I2S_BCK_FUNC (FUNC_I2S0_BCK)
#define I2S_WS_FUNC (FUNC_I2S0_WS)
#define I2S_DATA_FUNC (FUNC_I2S0_DATA)
#define I2S_DOUT_FUNC (FUNC_I2S0_DOUT)
#define I2S_DIN_FUNC (FUNC_I2S0_DIN)
#define I2S_NUM I2S_NUM_0

#define ssid AHAD
#define password 123456789

static const char *TAG = "AudioClassification";

int16_t audio_sample_buffer[AUDIO_VECTOR_SIZE];

void get_audio_sample()
{
    // Configure the I2S input pins
    gpio_pad_select_gpio(I2S_BCK_GPIO);
    gpio_set_direction(I2S_BCK_GPIO, GPIO_MODE_INPUT);
    gpio_set_direction(I2S_WS_GPIO, GPIO_MODE_INPUT);
    gpio_set_direction(I2S_DATA_GPIO, GPIO_MODE_INPUT);
    gpio_pullup_en(I2S_BCK_GPIO);
    gpio_pullup_en(I2S_WS_GPIO);
    gpio_pullup_en(I2S_DATA_GPIO);

    // Configure the I2S input mode
    i2s_config_t i2s_config = {
        .mode = I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM,
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
        .communication_format = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 2,
        .dma_buf_len = 64
    };
    i2s_pin_config_t i2s_pin_config = {
        .bck_io_num = I2S_BCK_GPIO,
        .ws_io_num = I2S_WS_GPIO,
        .data_out_num = I2S_DOUT_GPIO,
        .data_in_num = I2S_DIN_GPIO
   };

    // Install the I2S driver
    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &i2s_pin_config);

    // Read in the audio sample
    size_t bytes_read = 0;
    i2s_read(I2S_NUM, (char*)audio_sample_buffer, AUDIO_VECTOR_SIZE * 2, &bytes_read, portMAX_DELAY);
    ESP_LOGI(TAG, "Read %d bytes from I2S", bytes_read);
}

void trigger_alarm() {
  // Connect to the WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  // Send a request to the website to display a message
  http.begin("https://yourwebsite.com/display_message");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST("message=Alarm triggered");

  if (httpCode > 0) {
    // Request was successful
    Serial.printf("HTTP code: %d\n", httpCode);
  } else {
    // Request failed
    Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void classify_audio_task(void *pvParameters)
{
    // Initialize the model
    Eloquent::TinyML model;
    model.begin(model_data, sizeof(model_data));

    while (1) {
        // Read in the audio sample
        get_audio_sample();

        // Classify the audio sample
        float result = model.classify(audio_sample_buffer, AUDIO_VECTOR_SIZE);

        // Check the classification result
        if (result > 0.5) {
            // Fire alarm detected, trigger the alarm
             trigger_alarm();
        }

        // Wait for a bit before classifying the next audio sample
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    // Create the classify audio task
    xTaskCreate(classify_audio_task, "ClassifyAudio", 4096, NULL, 5, NULL);
}
   