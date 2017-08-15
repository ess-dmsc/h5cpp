#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/bind.hpp>
#include <object_handle.hpp>
#include <vector>
#include <string>

#include "object_handle_test.hpp"
using namespace boost::unit_test;


void test_default_construction()
  {
    hdf5::ObjectHandle handle;

    BOOST_CHECK(!handle.is_valid());
    BOOST_CHECK_EQUAL(handle.get_type(),hdf5::ObjectHandle::Type::BADOBJECT);
    BOOST_CHECK_THROW(handle.get_reference_count(),std::runtime_error);
    BOOST_CHECK_THROW(handle.increment_reference_count(),std::runtime_error);
    BOOST_CHECK_THROW(handle.decrement_reference_count(),std::runtime_error);
    BOOST_CHECK_NO_THROW(handle.close());
  }

test_suite *create_test_suite(hdf5::ObjectHandle::Type type)
{
  std::stringstream suite_name;
  suite_name<<"ObjectHandelTest_"<<type;
  test_suite *suite = BOOST_TEST_SUITE(suite_name.str());
  ObjectHandleTest *test = nullptr;
  switch(type)
  {
    case hdf5::ObjectHandle::Type::FILE:
      test = new FileObjectHandleTest("test.h5");
      break;
    case hdf5::ObjectHandle::Type::DATATYPE:
      test = new DatatypeObjectHandleTest("object_handle_datatype_test.h5");
      break;
    case hdf5::ObjectHandle::Type::DATASPACE:
      test = new DataspaceObjectHandleTest("object_handle_dataspace_test.h5");
      break;
    case hdf5::ObjectHandle::Type::GROUP:
      test = new GroupObjectHandleTest("object_handle_group_test.h5");
      break;
    case hdf5::ObjectHandle::Type::DATASET:
      test = new DatasetObjectHandleTest("object_handle_dataset_test.h5");
      break;
    case hdf5::ObjectHandle::Type::ATTRIBUTE:
      test = new AttributeObjectHandleTest("object_handle_attribute_test.h5");
      break;
    default:
      return nullptr;
  }

  suite->add(BOOST_TEST_CASE(boost::bind(&ObjectHandleTest::test_copy_assignment,test)));
  suite->add(BOOST_TEST_CASE(boost::bind(&ObjectHandleTest::test_move_assignment,test)));
  suite->add(BOOST_TEST_CASE(boost::bind(&ObjectHandleTest::test_copy_construction,test)));
  suite->add(BOOST_TEST_CASE(boost::bind(&ObjectHandleTest::test_move_construction,test)));
  suite->add(BOOST_TEST_CASE(boost::bind(&ObjectHandleTest::test_increment_reference_count,test)));
  suite->add(BOOST_TEST_CASE(boost::bind(&ObjectHandleTest::test_decrement_reference_count,test)));

  return suite;

}

bool init_function()
{

  framework::master_test_suite().add(BOOST_TEST_CASE(&test_default_construction));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::FILE));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::DATATYPE));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::DATASPACE));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::GROUP));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::DATASET));
  framework::master_test_suite().add(create_test_suite(hdf5::ObjectHandle::Type::ATTRIBUTE));

  return true;
}

int main(int argc,char **argv)
{
  return boost::unit_test::unit_test_main(&init_function,argc,argv);

}


