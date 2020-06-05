SELECT AVG(rating) FROM 
movies JOIN ratings on movies.id = ratings.movie_id
WHERE year = 2012

/* In 6.sql, write a SQL query to determine the average rating of all movies released in 2012.

    Your query should output a table with a single column and a single row (plus optional header) containing the average rating.
*/
