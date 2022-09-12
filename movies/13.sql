SELECT "name" FROM "people" JOIN "stars" ON "id"="person_id" WHERE "person_id" IN

(SELECT "person_id" FROM "stars" JOIN "movies" ON "movie_id"="id"
WHERE "movie_id" IN
(SELECT "movie_id" FROM "movies" JOIN "stars" ON "id"="movie_id" WHERE "person_id"=(SELECT "person_id" FROM "stars" JOIN "people" ON "id"="person_id" WHERE "name"="Kevin Bacon"))) AND "name"!="Kevin Bacon" GROUP BY "name"