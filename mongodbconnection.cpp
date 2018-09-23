#include "mongodbconnection.h"
#include <mongocxx/client.hpp>
#include <QDebug>
#include <stdlib.h>

MongoDBConnection::MongoDBConnection()
{
    // Deliberately empty
}

MongoDBConnection::MongoDBConnection(std::string database_name, std::string collection_name)
    : client(mongocxx::uri("mongodb://localhost:27017")), database(client[database_name]), collection(database[collection_name])
{
    if (!client) {
        qDebug() << "Client Error";
    }
}

MongoDBConnection::MongoDBConnection(std::string connection_uri, std::string database_name, std::string collection_name)
    : client(mongocxx::uri(connection_uri)), database(client[database_name]), collection(database[collection_name])
{
    if (!client) {
        qDebug() << "Client Error";
    }
}

void MongoDBConnection::change_collection(std::string new_collection_name)
{
    collection = database[new_collection_name];
}

mongocxx::client& MongoDBConnection::get_client()
{
    return client;
}

mongocxx::database& MongoDBConnection::get_database()
{
    return database;
}

mongocxx::collection& MongoDBConnection::get_collection()
{
    return collection;
}
