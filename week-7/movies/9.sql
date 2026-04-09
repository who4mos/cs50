-- 9. Names of all people who starred in a movie released in 2004, ordered by birth year

SELECT DISTINCT people.id AS id, people.name AS name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE year = 2004
ORDER BY birth;

-- SELECT id, name
-- FROM people
-- WHERE id IN (
--       SELECT person_id
--       FROM stars
--       WHERE movie_id IN (
--             SELECT id
--             FROM movies
--             WHERE year = 2004
--       )
-- )
-- ORDER BY birth;
