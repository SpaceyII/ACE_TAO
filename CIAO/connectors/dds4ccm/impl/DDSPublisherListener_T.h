/**
 * @author William R. Otte <wotte@dre.vanderbilt.edu>
 * @author Johnny Willemsen <jwillemsen@remedy.nl>
 *
 * $Id$
 *
 * Wrapper facade for NDDS.
 */

#ifndef DDSPUBLISHERLISTENER_T_H_
#define DDSPUBLISHERLISTENER_T_H_

#include "dds4ccm/idl/dds_rtf2_dcpsEC.h"

#include "dds4ccm/idl/dds_rtf2_dcpsC.h"
#include "dds4ccm/impl/dds4ccm_conf.h"

#if (CIAO_DDS4CCM_NDDS==1)
# include "ndds/ndds_cpp.h"
#endif

#if (CIAO_DDS4CCM_OPENDDS==1)
typedef ::DDS::PublisherListener DDSPublisherListener;
typedef ::DDS::DataWriter DDSDataWriter;
typedef ::DDS::OfferedDeadlineMissedStatus DDS_OfferedDeadlineMissedStatus;
typedef ::DDS::OfferedIncompatibleQosStatus DDS_OfferedIncompatibleQosStatus;
typedef ::DDS::LivelinessLostStatus DDS_LivelinessLostStatus;
typedef ::DDS::PublicationMatchedStatus DDS_PublicationMatchedStatus;
typedef ::DDS::ReliableWriterCacheChangedStatus DDS_ReliableWriterCacheChangedStatus;
#endif

namespace CIAO
{
  namespace DDS4CCM
  {
    template <typename DDS_TYPE, DDS4CCM_Vendor VENDOR_TYPE>
    class DDS_DataWriter_T;

    template <typename DDS_TYPE, DDS4CCM_Vendor VENDOR_TYPE>
    class CCM_DDS_PublisherListener_T :
      public virtual ::DDSPublisherListener
    {
    typedef DDS_DataWriter_T<DDS_TYPE, VENDOR_TYPE> DataWriter_type;
    public:
      /// Constructor
      CCM_DDS_PublisherListener_T (::DDS::PublisherListener_ptr p);

      /// Destructor
      virtual ~CCM_DDS_PublisherListener_T (void);

      virtual void
      on_offered_deadline_missed (
        ::DDSDataWriter *the_writer,
        const ::DDS_OfferedDeadlineMissedStatus & status);

      virtual void
      on_offered_incompatible_qos (
        ::DDSDataWriter *the_writer,
        const ::DDS_OfferedIncompatibleQosStatus & status);

      virtual void
      on_liveliness_lost (
        ::DDSDataWriter *the_writer,
        const ::DDS_LivelinessLostStatus & status);

      virtual void
      on_publication_matched (
        ::DDSDataWriter *the_writer,
        const ::DDS_PublicationMatchedStatus & status);

#if (CIAO_DDS4CCM_NDDS==1)
      virtual void
      on_reliable_reader_activity_changed (
        ::DDSDataWriter *the_writer,
        const ::DDS_ReliableReaderActivityChangedStatus & status);

      virtual void
      on_reliable_writer_cache_changed (
        ::DDSDataWriter *the_writer,
        const ::DDS_ReliableWriterCacheChangedStatus & status);
#endif

      ::DDS::PublisherListener_ptr get_publisher_listener (void);
    private:
      ::DDS::PublisherListener_var impl_;

      ::DDS::DataWriter_ptr
      get_datawriter_proxy (::DDSDataWriter * the_writer);
    };
  }
}

#include "dds4ccm/impl/DDSPublisherListener_T.cpp"

#endif /* DDSPUBLISHERLISTENER_T_H_ */
