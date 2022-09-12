SELECT "title" FROM "movies" JOIN "stars" ON "id"="movie_id"
WHERE "person_id" IN
((SELECT "person_id" FROM "stars" JOIN "people" ON "person_id"="id" WHERE "name"="Helena Bonham Carter")
AND
(SELECT "person_id" FROM "stars" JOIN "people" ON "person_id"="id" WHERE "name"="Johnny Depp"))