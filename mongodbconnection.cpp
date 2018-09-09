#include "mongodbconnection.h"
#include <mongocxx/client.hpp>
#include <QDebug>
#include <stdlib.h>

MongoDBConnection::MongoDBConnection()
{
    database_name = "";
    collection_name = "";
    client = nullptr;
    database = nullptr;
    collection = nullptr;
}

MongoDBConnection::MongoDBConnection(std::string connection_uri, std::string database_name, std::string collection_name)
{
    // This part initializes client
    if (client == nullptr) {
        client = new mongocxx::client(mongocxx::uri(connection_uri));
    } else {
        *client = mongocxx::client(mongocxx::uri(connection_uri));
    }

    // Checks if client is valid or not
    if (!(*client)) {
        delete client;
        qDebug() << "Error in 3 parametered constructor\n"
                 << "Client Error";
        std::exit(EXIT_FAILURE);
    }

    // This part is for initializing database and collection
    if (database == nullptr) {
        database = new mongocxx::database;
    }
    *database = (*client)[database_name];

    if (collection == nullptr) {
        collection = new mongocxx::collection;
    }
    *collection = (*database)[collection_name];
}

MongoDBConnection::MongoDBConnection(std::string database_name, std::string collection_name)
{
    // This part initializes client
    if (client == nullptr) {
        client = new mongocxx::client{mongocxx::uri{}};
    } else {
        *client = mongocxx::client{mongocxx::uri{}};
    }

    // Checks if client is valid or not
    if (!(*client)) {
        delete client;
        qDebug() << "Error in 2 parametered constructor\n"
                 << "Client Error";
        std::exit(EXIT_FAILURE);
    }

    // This part is for initializing database and collection
    if (database == nullptr) {
        database = new mongocxx::database;
    }
    *database = (*client)[database_name];

    if (collection == nullptr) {
        collection = new mongocxx::collection;
        *collection = (*database)[collection_name];
    }
}

MongoDBConnection::~MongoDBConnection()
{
    if (collection != nullptr) {
        delete collection;
    }

    if (database != nullptr) {
        delete database;
    }

    if (client != nullptr) {
        delete client;
    }
}
