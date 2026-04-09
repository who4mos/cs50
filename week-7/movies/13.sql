-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred

SELECT DISTINCT p2.name
FROM people p1
JOIN stars s1 ON p1.id = s1.person_id
JOIN movies ON s1.movie_id = movies.id
JOIN stars s2 ON movies.id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id
WHERE p1.name = 'Kevin Bacon' AND p1.birth = 1958
      AND p2.id != p1.id;

-- SELECT name
-- FROM people
-- WHERE id IN (
--       SELECT person_id
--       FROM stars
--       WHERE movie_id IN (
--             SELECT movie_id
--             FROM stars
--             WHERE person_id = (
--                   SELECT id
--                   FROM people
--                   WHERE name = 'Kevin Bacon'
--                   AND birth = 1958
--             )
--       )
-- )
-- AND id != (
--     SELECT id
--     FROM people
--     WHERE name = 'Kevin Bacon'
--     AND birth = 1958
-- );
