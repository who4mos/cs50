-- 11. Titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated

SELECT DISTINCT title
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;

-- SELECT title
-- FROM movies
-- WHERE id IN (
--        SELECT movie_id
--        FROM stars
--        WHERE person_id = (
--               SELECT id
--               FROM people
--               WHERE name = 'Chadwick Boseman'
--        )
-- )
-- ORDER BY (
--       SELECT rating
--       FROM ratings
--       WHERE ratings.movie_id = movies.id
-- ) DESC
-- LIMIT 5;
