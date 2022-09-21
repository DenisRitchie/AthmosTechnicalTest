# Ecosystem of Services

The company is looking to develop a series of microservices in charge of managing the information of
some investors, so the developer responsible for this activity needs to be able to perform the following
tasks:

* Create a service where you create an Investor
* Create a service where you delete an Investor
* Create a service where you modify an Investor
* Create a service where you list inverters and we can make search filters such as name,
  email, phone (do not forget the paging).
* Create the respective routes for the authentication process for the later use of the rest of the
  routes.

__Entity "investor" must contain at least the following information:__

* Name
* Email
* Phone

__Keep in mind that:__

* The database you will use for this example will be a JSON file oriented database inside the
  project folder (DO NOT USE DATABASE LIKE MYSQL, SQL SERVER OR OTHER).
* Must use a microservices based architecture.
* You must use the "repository" pattern for the management of the models that are in charge of
  working the data.
* Remember to use unit tests.
* Remember to apply security to the routes, for example JWT or other type of security.
* You should use functional programming as little as possible, use object-oriented programming
  instead.
* Do not forget the S.O.L.I.D. principles.

__At the end of this test:__

* Upload the documentation of your services to POSTMAN and send the "collection.json".
