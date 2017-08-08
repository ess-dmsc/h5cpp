#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ObjectHandleTest
#include <boost/test/unit_test.hpp>
#include <object_handle.hpp>



BOOST_AUTO_TEST_SUITE(ObjectHandleTest)
  

  BOOST_AUTO_TEST_SUITE(DefaultConstructionTest)

    BOOST_AUTO_TEST_CASE(test_construction)
    {
      hdf5::ObjectHandle handle;
      
      BOOST_CHECK(!handle.is_valid());
      BOOST_CHECK_EQUAL(handle.get_type(),hdf5::ObjectHandle::Type::BADOBJECT);
      BOOST_CHECK_THROW(handle.get_reference_count(),std::runtime_error);
      BOOST_CHECK_THROW(handle.increment_reference_count(),std::runtime_error);
      BOOST_CHECK_THROW(handle.decrement_reference_count(),std::runtime_error);
      BOOST_CHECK_NO_THROW(handle.close());

    }

  BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()
