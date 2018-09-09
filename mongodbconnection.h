#ifndef MONGODBCONNECTION_H
#define MONGODBCONNECTION_H

#include <string>
#include <mongocxx/client.hpp>

class MongoDBConnection
{
public:
    MongoDBConnection();
    MongoDBConnection(std::string connection_uri, std::string database_name, std::string collection_name);
    MongoDBConnection(std::string database_name, std::string collection_name);
    ~MongoDBConnection();
private:
    std::string database_name;
    std::string collection_name;
    mongocxx::client *client;
    mongocxx::database *database;
    mongocxx::collection *collection;
};

#endif // MONGODBCONNECTION_H
