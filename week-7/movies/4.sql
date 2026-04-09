-- 4. Number of movies with a 10.0 rating

SELECT COUNT(*)
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE rating = 10.0;

-- SELECT COUNT(*) AS n
-- FROM movies
-- WHERE id IN (
--       SELECT movie_id
--       FROM ratings
--       WHERE rating = 10.0
-- );
