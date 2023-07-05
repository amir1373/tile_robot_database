# tile_robot_database

this is just a database for the tile robot!

to install libpqxx see [this link](https://github.com/jtv/libpqxx)

## build

Before building, you must clone the libpqxx repository. this is necessary.

``` git submodule init && git submodule update ```

to compile this code run the builder script:

```./builder.bash```

or

``` bash builder.bash ```

## Run

To run this goes into the build folder and run the main exec file like this:

``` ./main $DB_NAME $USERNAME $PASSWORD $HOST $PORT ```

### Docker Compose

you can use postgres in docker, not in your host!
for this, go into root of repository and run this:

``` docker compose up ```

Note: before that you must install docker and docker-compose
