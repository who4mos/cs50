-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred

SELECT title
FROM movies
JOIN stars s1 ON movies.id = s1.movie_id
JOIN people p1 ON s1.person_id = p1.id
JOIN stars s2 ON movies.id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id
WHERE p1.name = 'Bradley Cooper'
AND p2.name = 'Jennifer Lawrence';

-- SELECT title
-- FROM movies
-- WHERE id IN (
--       SELECT movie_id
--       FROM stars
--       WHERE person_id = (
--             SELECT id
--             FROM people
--             WHERE name = 'Jennifer Lawrence'
--       )
-- ) AND id IN (
--       SELECT movie_id
--       FROM stars
--       WHERE person_id = (
--             SELECT id
--             FROM people
--             WHERE name = 'Bradley Cooper'
--       )
-- ); 
