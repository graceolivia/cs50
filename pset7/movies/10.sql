SELECT DISTINCT(people.name) FROM
people JOIN directors ON people.id = directors.person_id 
JOIN movies ON directors.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE rating >= 9.0

/* Executing 10.sql results in a table with 1 column and 1,841 rows.
In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.

    Your query should output a table with a single column for the name of each person.
*/
