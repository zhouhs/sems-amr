#include "Snmp.h"

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "semsStats.h"

#define MOD_NAME "snmp"

EXPORT_MODULE_FUNC(SnmpFactory);

DEFINE_MODULE_INSTANCE(SnmpFactory, MOD_NAME)

SnmpFactory::SnmpFactory(const string& name)
  : AmPluginFactory(name)
{
}

void SnmpFactory::run()
{
  // Start SNMP Agent
  agent_running.set(true);

  snmp_enable_stderrlog();

  /* make us a agentx client. */
  netsnmp_ds_set_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_AGENT_ROLE, 1);

  /* initialize tcpip, if necessary */
  SOCK_STARTUP;

  /* initialize the agent library */
  init_agent("sems");

  snmp_log(LOG_INFO,"SEMS SNMP-Agent initialized.\n");

  /* initialize mib code here */
  init_semsStats();

  /* example-demon will be used to read example-demon.conf files. */
  init_snmp("sems");

  snmp_log(LOG_INFO,"SEMS SNMP-Agent is up and running.\n");

  /* your main loop here... */
  while(agent_running.get()) {
    /* if you use select(), see snmp_select_info() in snmp_api(3) */
    /*     --- OR ---  */
    agent_check_and_process(1); /* 0 == don't block */
    snmp_log(LOG_INFO,"one time.\n");
  }

  /* at shutdown time */
  snmp_shutdown("sems");
  SOCK_CLEANUP;
}

void SnmpFactory::on_stop()
{
  agent_running.set(false);
}

int SnmpFactory::onLoad()
{
  start();
  return 0;
}

void SnmpFactory::onUnload()
{
  stop();
  join();
};
