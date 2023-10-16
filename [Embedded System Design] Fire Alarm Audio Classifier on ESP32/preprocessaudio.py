import librosa
import pandas as pd
import glob

# Create an empty list to store the features for each audio file
all_features = []
audio_files = glob.glob("D:\7th Semester\EE-423 Embedded System Design\Project\*.wav")
# Iterate over the audio files
for audio_file in audio_files:
    # Load the audio file using Librosa
    audio, sample_rate = librosa.load(audio_file)

    # Extract the spectral centroids, MFCCs, and chroma features
    spectral_centroids = librosa.feature.spectral_centroid(audio, sr=sample_rate)[0]
    mfccs = librosa.feature.mfcc(audio, sr=sample_rate)
    chroma = librosa.feature.chroma_stft(audio, sr=sample_rate)

    # Flatten the features into a single array
    features = np.concatenate([spectral_centroids, mfccs, chroma])

    # Add the features to the list
    all_features.append(features)

# Convert the list of features to a Pandas data frame
df = pd.DataFrame(all_features)

# Save the data frame to a .csv file
df.to_csv("alarm_data.csv", index=False)