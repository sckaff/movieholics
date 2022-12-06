# Import the pandas library
# To install the pandas library, run the following command in the terminal: pip install pandas
import pandas as pd

# Reading the data from the tsv files
df_basics = pd.read_csv("Data/title.basics.tsv", sep='\t', index_col="tconst")
df_ratings = pd.read_csv("Data/title.ratings.tsv", sep='\t', index_col="tconst")

# Select only the columns we need
df_basics2 = df_basics[["titleType", "isAdult", "primaryTitle", "startYear", "runtimeMinutes", "genres"]] 

# Remove adult movies
df_basics3 = df_basics2[df_basics2["isAdult"] == 0] 

# Remove TV shows
df_basics4 = df_basics3[df_basics3["titleType"] == "movie"] 

# Remove movies with no runtime
df_basics5 = df_basics4.drop(df_basics4[df_basics4['runtimeMinutes'] == "\\N"].index) 

# Remove movies with no genre
df_basics6 = df_basics5.drop(df_basics5[df_basics5['genres'] == "\\N"].index) 

# Remove isAdult and titleType columns
df_basics7 = df_basics6.drop(columns=["isAdult", "titleType"]) 

# Merge the two dataframes
merged_df = pd.concat([df_basics7, df_ratings], axis=1, join="inner") 

# Remove all but the first genre of a each movie
merged_df['genres'] = merged_df['genres'].apply(lambda x: x.strip().split(',')[0]) 

# Remove genres with less than 10000 movies
remove_small_genres = merged_df["genres"].value_counts() < 10000 

# Get the names of the genres to remove
remove_small_genres2 = remove_small_genres[remove_small_genres == True].index.tolist() 

# Remove Sci-Fi from the list of genres to remove. We like sci-fi movies.
remove_small_genres2.remove('Sci-Fi') 

# Remove the small genres
merged_df2 = merged_df[~merged_df.genres.isin(remove_small_genres2)] 

# Normalize the runtime
merged_df2['runtimeMinutes_norm'] = (merged_df2['runtimeMinutes'].apply(lambda x: float(x)) - merged_df2['runtimeMinutes'].apply(lambda x: float(x)).mean()) / merged_df2['runtimeMinutes'].apply(lambda x: float(x)).std()

# Normalize the rating
merged_df2['averageRating_norm'] = (merged_df2['averageRating'].apply(lambda x: float(x)) - merged_df2['averageRating'].apply(lambda x: float(x)).mean()) / merged_df2['averageRating'].apply(lambda x: float(x)).std()

# Normalize the popularity
merged_df2['numVotes_norm'] = (merged_df2['numVotes'].apply(lambda x: float(x)) - merged_df2['numVotes'].apply(lambda x: float(x)).mean()) / merged_df2['numVotes'].apply(lambda x: float(x)).std()

# Remove commas from the movie titles
merged_df2["primaryTitle"] = merged_df2["primaryTitle"].str.replace(',','') 

# Export
merged_df2.to_csv("Data/merged_data.csv")