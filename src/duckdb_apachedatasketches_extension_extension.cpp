#define DUCKDB_EXTENSION_MAIN

#include "duckdb_apachedatasketches_extension_extension.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/common/string_util.hpp"
#include "duckdb/function/scalar_function.hpp"
#include "duckdb/main/extension_util.hpp"
#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>

// OpenSSL linked through vcpkg
#include <openssl/opensslv.h>

namespace duckdb {

inline void DuckdbApachedatasketchesExtensionScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
    auto &name_vector = args.data[0];
    UnaryExecutor::Execute<string_t, string_t>(
	    name_vector, result, args.size(),
	    [&](string_t name) {
			return StringVector::AddString(result, "DuckdbApachedatasketchesExtension "+name.GetString()+" 🐥");;
        });
}

inline void DuckdbApachedatasketchesExtensionOpenSSLVersionScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
    auto &name_vector = args.data[0];
    UnaryExecutor::Execute<string_t, string_t>(
	    name_vector, result, args.size(),
	    [&](string_t name) {
			return StringVector::AddString(result, "DuckdbApachedatasketchesExtension " + name.GetString() +
                                                     ", my linked OpenSSL version is " +
                                                     OPENSSL_VERSION_TEXT );;
        });
}

static void LoadInternal(DatabaseInstance &instance) {
    // Register a scalar function
    auto duckdb_apachedatasketches_extension_scalar_function = ScalarFunction("duckdb_apachedatasketches_extension", {LogicalType::VARCHAR}, LogicalType::VARCHAR, DuckdbApachedatasketchesExtensionScalarFun);
    ExtensionUtil::RegisterFunction(instance, duckdb_apachedatasketches_extension_scalar_function);

    // Register another scalar function
    auto duckdb_apachedatasketches_extension_openssl_version_scalar_function = ScalarFunction("duckdb_apachedatasketches_extension_openssl_version", {LogicalType::VARCHAR},
                                                LogicalType::VARCHAR, DuckdbApachedatasketchesExtensionOpenSSLVersionScalarFun);
    ExtensionUtil::RegisterFunction(instance, duckdb_apachedatasketches_extension_openssl_version_scalar_function);
}

void DuckdbApachedatasketchesExtensionExtension::Load(DuckDB &db) {
	LoadInternal(*db.instance);
}
std::string DuckdbApachedatasketchesExtensionExtension::Name() {
	return "duckdb_apachedatasketches_extension";
}

std::string DuckdbApachedatasketchesExtensionExtension::Version() const {
#ifdef EXT_VERSION_DUCKDB_APACHEDATASKETCHES_EXTENSION
	return EXT_VERSION_DUCKDB_APACHEDATASKETCHES_EXTENSION;
#else
	return "";
#endif
}

} // namespace duckdb

extern "C" {

DUCKDB_EXTENSION_API void duckdb_apachedatasketches_extension_init(duckdb::DatabaseInstance &db) {
    duckdb::DuckDB db_wrapper(db);
    db_wrapper.LoadExtension<duckdb::DuckdbApachedatasketchesExtensionExtension>();
}

DUCKDB_EXTENSION_API const char *duckdb_apachedatasketches_extension_version() {
	return duckdb::DuckDB::LibraryVersion();
}
}

#ifndef DUCKDB_EXTENSION_MAIN
#error DUCKDB_EXTENSION_MAIN not defined
#endif
