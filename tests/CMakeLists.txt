include(TestUtils)

set(googletest_commit_hash "f8d7d77c06936315286eb55f8de22cd23c188571")

fetch_googletest(HASH "${googletest_commit_hash}" HIDDEN)

include(GoogleTest)
gtest_discover_tests()
