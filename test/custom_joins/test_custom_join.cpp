#include "catch.hpp"
#include "test_helpers.hpp"
#include "duckdb/parser/parser.hpp"
#include "duckdb/planner/logical_operator.hpp"
#include "duckdb/main/connection_manager.hpp"

#include <chrono>
#include <thread>

using namespace duckdb;
using namespace std;

TEST_CASE("Test CUSTOM JOIN API", "[custom_join]") {
	DBConfig config;
	config.options.maximum_threads = 8;
	DuckDB db(nullptr, &config);
	Connection con(db);

	REQUIRE_NO_FAIL(con.Query("CREATE TABLE Movies (mID INTEGER, Name VARCHAR(255), PRIMARY KEY(mID))"));
	REQUIRE_NO_FAIL(con.Query("INSERT INTO Movies VALUES (1, 'A'), (2, 'B'), (3, 'C')"));
	REQUIRE_NO_FAIL(con.Query("CREATE TABLE Ratings (rID INTEGER, mID INTEGER, Rating INTEGER, PRIMARY KEY(rID))"));
	REQUIRE_NO_FAIL(con.Query("INSERT INTO Ratings VALUES (1,1,5), (2,3,3), (3,2,4), (4,2,1), (5,3,5)"));
	auto joined_table = con.SendQuery(R"(SELECT * FROM Movies FULL OUTER JOIN Ratings ON Movies.mID = Ratings.mID)");

	idx_t count = 0;
	while (true) {
		auto chunk = joined_table->Fetch();
		if (!chunk) {
			break;
		}
		if (chunk->size() == 0) {
			break;
		}
		count += chunk->size();
	}
	
	REQUIRE(5 - count == 0);
}

