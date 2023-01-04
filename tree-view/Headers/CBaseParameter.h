#pragma once


#include <vector>
#include <stdint.h>
#include <string>



class CBaseParameter
{
  public:
    enum eParameterTypeId {
      PTId_uint32,
      PTId_int32,
      PTId_uint16,
      PTId_int16,
      PTId_uint8,
      PTId_int8,
      PTId_float,
      PTId_double,
      PTId_undef,
    };
    CBaseParameter(eParameterTypeId p_TypeId, std::string p_name, std::string p_default = "", std::string p_description = "") :
      m_TypeId(p_TypeId),
      m_name(p_name),
      m_default(p_default),
      m_description(p_description)
    {
      if(p_default=="") {
        m_default = "0";
      }
    }
    virtual ~CBaseParameter();
    std::string GetName() {return m_name;}
    std::string GetDefault() {return m_default;}
    void SetDefault(std::string p_val) {m_default = p_val;}
  protected:
  private:
    eParameterTypeId m_TypeId;
    std::string m_name;
    std::string m_default;
    std::string m_description;
};



class CParameterRoot
{
  public :
    ~CParameterRoot(){ for (auto pr : m_ParamList){delete pr;}}
    CParameterRoot(uint32_t p_moduleid, uint32_t p_messageid, std::string p_NodeDevice) : m_ModuleId(p_moduleid), m_MessageId(p_messageid), m_NodeDevice(p_NodeDevice) {}
    /// commands for list construction:
    void AddParameter(CBaseParameter* p_Par) {m_ParamList.push_back(p_Par);}
    void SetParameterValue(uint32_t p_ParId, std::string p_val) {
          m_ParamList.at(p_ParId)->SetDefault(p_val);
          }
    std::string GetNodeDevice() { return m_NodeDevice; }
    ///
    void SerializeCommand(std::vector<uint8_t>& p_pData) {}
    ///
    std::vector<CBaseParameter*>* GetParameterVector() {return &m_ParamList;}
  private :
    uint32_t                     m_ModuleId;
    uint32_t                     m_MessageId;
    std::string                  m_NodeDevice;
    std::vector<CBaseParameter*> m_ParamList;
};




