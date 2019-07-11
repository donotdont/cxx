#include <cstdint>
#include <iostream>
#include <vector>

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/types.hpp>

using namespace bsoncxx;

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::array;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_document;
using bsoncxx::builder::basic::sub_array;

int main(int, char**) {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{
       "mongodb://localhost/testdb"
       }
    };

    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["testcollection"];
    //document << "hello" << "world";

    /*collection.insert_one(document.view());
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }*/

    // Working with bson
    /*bsoncxx::builder::basic::document basic_builder{};
    basic_builder.append(kvp("hello2kvp","world2kvp"));
    bsoncxx::document::value document_value = basic_builder.extract();

    collection.insert_one(document_value.view());*/

    // Working with bson2
    auto doc = builder::basic::document{};
    auto dod = builder::basic::document{};
    auto doe = builder::basic::document{};
    auto arr = builder::basic::array{};
 
    doc.append(kvp("foo","bar"));
    doc.append(kvp("baz", types::b_bool{false}));
    doc.append(kvp("garply", types::b_double{3.14159}));

    doc.append(kvp("a key", "a value"),
	       kvp("another key", "another value"),
	       kvp("moar keys", "moar values"));

    arr.append("hello");
    arr.append(false, types::b_bool{false}, types::b_double{1.234});
    
    dod.append(kvp("arraynaja",arr));

    // Working with bson3
    doe.append(kvp("subdocument key", [](sub_document subdoe){
	       		subdoe.append(kvp("subdoc key", "subdoc value"),
				 kvp("anather subdoc key", types::b_int64{1212}));
	       }),
	       kvp("subarray key", [](sub_array subarr){
			subarr.append(1,
				      types::b_bool{false},
				      5,
				      [](sub_document subdoee){
				      	subdoee.append(kvp("such","nesting"),
							kvp("much","recurse"));
				      });	       
	       }));

    collection.insert_one(doe.view());

    // Find DB
    auto cursor = collection.find({});

    for(auto&& doc : cursor){
    	std::cout << bsoncxx::to_json(doc) << std::endl;
    }

    // Insert One
    /*auto builder = bsoncxx::builder::stream::document{};
  bsoncxx::document::value doc_value = builder
  << "name" << "MongoDB"
  << "type" << "database"
  << "count" << 1
  << "versions" << bsoncxx::builder::stream::open_array
    << "v3.2" << "v3.0" << "v2.6"
  << close_array
  << "info" << bsoncxx::builder::stream::open_document
    << "x" << 203
    << "y" << 102
  << bsoncxx::builder::stream::close_document
  << bsoncxx::builder::stream::finalize;

  collection.insert_one(doc_value.view());*/

   // Insert Many
   /*std::vector<bsoncxx::document::value> documents;
   for(int i=0; i<100; i++){
      documents.push_back(bsoncxx::builder::stream::document{} << "i" << i << finalize);
   }
   collection.insert_many(documents);

  auto cursor = collection.find({});

  for(auto&& doc : cursor){
  	std::cout << bsoncxx::to_json(doc) << std::endl;
  }*/

    // Find
    /*mongocxx::cursor cursor = collection.find({});

    for(auto doc : cursor){
    	std::cout << bsoncxx::to_json(doc) << "\n";
    }*/

    // Find One
    /*bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result = 
	    collection.find_one(bsoncxx::builder::stream::document{} << "i" << 71 << finalize);
    if(maybe_result){
    	std::cout << bsoncxx::to_json(*maybe_result) << "\n";
    }*/

    // Find Many
    /*mongocxx::cursor cursor = collection.find(
	bsoncxx::builder::stream::document{} << "i" << open_document << "$gt" << 50 << "$lte" << 100 << close_document << finalize
		    );
    for(auto doc : cursor){
    	std::cout << bsoncxx::to_json(doc) << "\n";
    }*/

    // Update Many
    /*bsoncxx::stdx::optional<mongocxx::result::update> result = collection.update_many(
	bsoncxx::builder::stream::document{} << "i" << open_document << "$lt" << 100 << close_document << finalize,
	bsoncxx::builder::stream::document{} << "$inc" << open_document << "i" << 100 << close_document << finalize
		    );
    if(result){
    	std::cout << result->modified_count() << "\n";
    }*/

    // Delete
    //collection.delete_one(bsoncxx::builder::stream::document{} << "i" << 110 << finalize);

    // Delete Many
    /*bsoncxx::stdx::optional<mongocxx::result::delete_result> result = 
    collection.delete_many(
	bsoncxx::builder::stream::document{} << "i" << open_document << "$gte" << 100 << close_document << finalize
		    );

    if(result){
    	std::cout << result->deleted_count() << "\n";
    }*/

    // Create Indexes
    /*auto index_specification = bsoncxx::builder::stream::document{} << "i" << 1 << finalize;
    collection.create_index(std::move(index_specification));*/

}
