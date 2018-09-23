#ifndef MONGODBCONNECTION_H
#define MONGODBCONNECTION_H

#include <string>
#include <mongocxx/client.hpp>

class MongoDBConnection
{
public:
    // Constructors and destructor
    MongoDBConnection();
    MongoDBConnection(std::string database_name, std::string collection_name);
    MongoDBConnection(std::string connection_uri, std::string database_name, std::string collection_name);
    ~MongoDBConnection() = default;

    void change_collection(std::string new_collection_name);

    mongocxx::client& get_client();
    mongocxx::database& get_database();
    mongocxx::collection& get_collection();

private:
    mongocxx::client client;
    mongocxx::database database;
    mongocxx::collection collection;
};

#endif // MONGODBCONNECTION_H
