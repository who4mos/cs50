SELECT AVG(rating) AS "avg 2012"
FROM movies
JOIN ratings
ON movies.id = ratings.movie_id
WHERE year = 2012;

