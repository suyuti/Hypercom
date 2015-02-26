#ifndef _POSSERVER_HPP_
#define _POSSERVER_HPP_

// Hostun baglantisini dinleyen thread
void PosServerThreadProc(UNSIGNED, VOID*);
void PosServerConnectThreadProc(UNSIGNED, VOID*);

class HyperwareMain;
void OnCmdSiparisVar(HyperwareMain *pApp);
void OnCmdConnectionTest(HyperwareMain *pApp, INT sock);
void OnCmdVersionCheck(HyperwareMain *pApp, INT sock);

enum cmds {
	cmdSiparisVar,
	cmdConnectionTest,
	cmdVersionCheck
};

#endif
