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

TEST_CASE("Test comment in CPP CUSTOM API", "[custom_join]") {
	DBConfig config;
	config.options.maximum_threads = 8;
	DuckDB db(nullptr, &config);
	Connection con(db);

	REQUIRE_NO_FAIL(con.Query("select setseed(0.1); CREATE TABLE T0 AS SELECT DISTINCT (RANDOM()*9999999)::BIGINT "
	                          "record_nb, 0.0 x_0, 1.0 y_0 FROM range(1000000) tbl"));
	REQUIRE_NO_FAIL(con.Query("CREATE TABLE T1 AS SELECT record_nb, 0.0 x_1, 1.0 y_1 FROM T0"));
	REQUIRE_NO_FAIL(con.Query("CREATE TABLE T2 AS SELECT record_nb, 0.0 x_2, 1.0 y_2 FROM T0"));
	REQUIRE_NO_FAIL(con.Query("CREATE TABLE T3 AS SELECT record_nb, 0.0 x_3, 1.0 y_3 FROM T0"));
	auto result = con.SendQuery(R"(
        SELECT T0.record_nb,
            T1.x_1 x_1,
            T1.y_1 y_1,
            T2.x_2 x_2,
            T2.y_2 y_2,
            T3.x_3 x_3,
            T3.y_3 y_3
         FROM T0
           INNER JOIN T1 on T0.record_nb = T1.record_nb
           INNER JOIN T2 on T0.record_nb = T2.record_nb
           INNER JOIN T3 on T0.record_nb = T3.record_nb
    )");

	idx_t count = 0;
	while (true) {
		auto chunk = result->Fetch();
		if (!chunk) {
			break;
		}
		if (chunk->size() == 0) {
			break;
		}
		count += chunk->size();
	}

	REQUIRE(951468 - count == 0);
}
