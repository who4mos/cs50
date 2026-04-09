-- 10. Names of all directors who have directed a movie that got a rating of at least 9.0

SELECT DISTINCT people.name
FROM people
JOIN directors ON people.id = directors.person_id
JOIN movies ON directors.movie_id = movies.id
JOIN ratings on movies.id = ratings.movie_id
WHERE rating >= 9.0;

-- SELECT name
-- FROM people
-- WHERE id IN (
--       SELECT person_id
--       FROM directors
--       WHERE movie_id
--       IN (
--          SELECT movie_id
--          FROM ratings
--          WHERE rating >= 9.0
--       )
-- );
