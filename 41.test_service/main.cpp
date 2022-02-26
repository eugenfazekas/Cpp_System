/*CopyRight reserved to awinsyspro.com 2019-2020
Sample Code for Windows Service- Part2 only */
#include <Windows.h> //Windows Service
#include <iostream>
using namespace std;
//----Global Variable Declarations------//
//ServiceName
#define SERVICE_NAME TEXT("ASPService") 
// Service Status Structure
SERVICE_STATUS ServiceStatus = { 0 }; 
//Service Status Handle for Register the Service
SERVICE_STATUS_HANDLE hServiceStatusHandle = NULL;
// Event Handle for Service
HANDLE hServiceEvent = NULL; 
//---- Windows Service Functions Declarations----//
// Service Main Function
void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv); 
// Service Control Handler
void WINAPI ServiceControlHandler(DWORD dwControl); 
void ServiceReportStatus(
     DWORD dwCurrentState,
     DWORD dwWin32ExitCode,
     DWORD dwWaitHint); // Service Report Status
// ServiceInit Fun
void ServiceInit(DWORD dwArgc, LPTSTR *lpArgv); 
// Service install Fun
void ServiceInstall(void);
// Service delete Fun
void ServiceDelete(void);
// Service start Fun
void ServiceStart(void);
// Service Stop Fun
void ServiceStop(void);
//---------- Main Function------------//
int main(int argc, CHAR *argv[])
{
  cout << "In main fun Start" << endl;
  // Local Variable Definition
  BOOL bStServiceCtrlDispatcher = FALSE;
  // Functional Logic Starts Here
  if (lstrcmpiA(argv[1], "install") == 0)
  {
    //Call Service Install Fun.
     ServiceInstall();
     cout << "Installation Success" << endl;
  }// if
 else if (lstrcmpiA(argv[1], "Start") == 0)
  {
     //Call Service Start Fun.
     ServiceStart();
     cout << "ServiceStart Success" << endl;
   }// else if
  else if (lstrcmpiA(argv[1], "stop") == 0)
  {
     //Call Service Stop Fun.
     ServiceStop();
     cout << "ServiceStop Success" << endl;
   }// else if
  else if (lstrcmpiA(argv[1], "delete") == 0)
  {
       //Call Service delete Fun.
       ServiceDelete();
       cout << "ServiceDelete" << endl;
   }
  else
  {
    //STEP-1 Fill the Service Table Entry (2D Array)
     SERVICE_TABLE_ENTRY DispatchTable[] =
     {
       { SERVICE_NAME,(LPSERVICE_MAIN_FUNCTION)ServiceMain},
       { NULL, NULL }
     };
//STEP-2 -> Start Service Control Dispatcher
bStServiceCtrlDispatcher = StartServiceCtrlDispatcher(
                            DispatchTable);
 if (FALSE == bStServiceCtrlDispatcher)
  {
    cout << "StartServiceCtrlDispatcher Failed" << endl;
    cout<<"Error Code - "<<GetLastError() << endl;
  }
  else
  {
    cout << "StartServiceCtrlDispatcher Success" << endl;
   }// if
  }// else
  cout << "In main fun End" << endl;
  system("PAUSE");
  return 0;
}
//--------------End of Main Function--------------//
//--------- ServiceMain Function Definition--------//
void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv)
{
   cout << "ServiceMain Start" << endl;
   // Local Variable definitions
   BOOL bServiceStatus = FALSE;
  /* STEP -1 ->Registering Service Control Handler 
             Function to SCM */
   hServiceStatusHandle = RegisterServiceCtrlHandler(
                           SERVICE_NAME,
                           ServiceControlHandler );
   if (NULL == hServiceStatusHandle)
   {
     cout << " RegisterServiceCtrlHandler Failed " << endl;
     cout << "Error Code - "<<GetLastError() << endl;
    }
   else
   {
    cout << "RegisterServiceCtrlHandler Success" << endl;
    }
  //STEP-2-> SERVICE_STATUS Initial Setup Here
  ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
  ServiceStatus.dwServiceSpecificExitCode = 0;
  /*STEP-3-> Call Service Report Status for Notifying 
            Initial Setup */
  ServiceReportStatus(
             SERVICE_START_PENDING, 
             NO_ERROR, 
             3000);
  // STEP-4-> Check the Service Status
   bServiceStatus = SetServiceStatus(
                     hServiceStatusHandle,
                     &ServiceStatus);
   if (FALSE == bServiceStatus)
   {
     cout << "Service Status Initial Setup FAILED = " <<
      GetLastError() << endl;
   }
   else
   {
    cout << "Service Status initial Setup SUCCESS" << endl;
   }
    //STEP-5 -> Call ServiceInit Fun
    ServiceInit(dwArgc, lpArgv);
    cout << "ServiceMain End" << endl;
}//------------End of ServiceMain-----------------//

//----- Service Control Handler Definitions---------//
void WINAPI ServiceControlHandler(DWORD dwControl)
{
  cout << "ServiceControlHandler" << endl;
   switch (dwControl)
   {
     case SERVICE_CONTROL_STOP:
     {
        //Call ServiceReportStatus Function
        ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
        cout << "Service stopped" << endl;
        break;
      }
    default:
        break;
   }//Switch
   cout << "ServiceControlHandler" << endl;
} //-----End of Service Control Handler fun------//










/*CopyRight reserved to awinsyspro.com 2019-2020
Sample Code for Windows Service- Part3 only */

//--------------ServiceInit Definitions----------//
void ServiceInit(DWORD dwArgc, LPTSTR *lpArgv)
{
   cout << "ServiceInit Start" << endl;
   //STEP-1 -> Create Event
   hServiceEvent = CreateEvent(
                   NULL,//Security Attributes
                   TRUE,//MANUAL Reset Event
                   FALSE,//Non-Signaled
                   NULL);//Name of Event
   if (NULL == hServiceEvent)
   {
     /* Call ServiceReportStatus Fun to Notify 
     SCM for Current Status of Service*/
     ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
   }
  else
   {
     /* Call ServiceReportStatus Fun to Notify
      SCM for Current Status of Service*/
      ServiceReportStatus(SERVICE_RUNNING, NO_ERROR, 0);
    }
 //STEP-2-> Check Whether to stop the Service
 while (1)
 {
   //WaitforSingleObject Which wait event to be Signaled.
   WaitForSingleObject(hServiceEvent, INFINITE);
   //Send Report status to SCM
   ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
  }
  cout << "ServiceInit End" << endl;
}//-------End of ServiceInit --------------------//

//--------Service Report Status Fun Definitions-----//
void ServiceReportStatus(
DWORD dwCurrentState,
DWORD dwWin32ExitCode,
DWORD dwWaitHint)
{
  cout << "ServiceReportStatus Start" << endl;
  // Local variable Definitions
  static DWORD dwCheckPoint = 1;
  BOOL bSetServiceStatus = FALSE;
  // STEP-1 Fill The SERVICE_STATUS Structure
  ServiceStatus.dwCurrentState = dwCurrentState;
  ServiceStatus.dwWin32ExitCode = dwWin32ExitCode;
  ServiceStatus.dwWaitHint = dwWaitHint;
  // STEP-2 -> Check the Current State of Service
  //Service is about to start
  if (dwCurrentState == SERVICE_START_PENDING)
  {
    ServiceStatus.dwControlsAccepted = 0;
  }
  else
  {
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
  }
  //STEP-3 -> Progress for Service operation
  if ((dwCurrentState == SERVICE_RUNNING) || 
      (dwCurrentState == SERVICE_STOPPED))
  {
     ServiceStatus.dwCheckPoint = 0;
  }
  else
  {
     ServiceStatus.dwCheckPoint = dwCheckPoint++;
   }
  //STEP-4 -> Notify the current status of SCM
    bSetServiceStatus = SetServiceStatus(
                         hServiceStatusHandle,
                         &ServiceStatus);
  if (FALSE == bSetServiceStatus)
  {
    cout << "Service Status FAILED " << endl;
    cout<<"Error No - " << GetLastError() <<endl;
  }
  else
  {
     cout << "Service Status SUCCESS" << endl;
   }// if
  cout << "ServiceReportStatus End" << endl;
}
//---- End of ServiceReportStatus Fun Definition ------//







/*CopyRight reserved to awinsyspro.com 2019-2020
Sample Code for Windows Service- Part4 only */
//------ServiceInstall Definitions---------------//
void ServiceInstall(void)
{
   cout << "ServiceInstall Start" << endl;
   // Local Variable Definitions
   SC_HANDLE hScOpenSCManager = NULL;
   SC_HANDLE hScCreateService = NULL;
   DWORD dwGetModuleFileName = 0;
   TCHAR szPath[MAX_PATH];
   /*STEP-1 -> GetModuleFileName Get the 
   Executable file from SCM*/ 
  dwGetModuleFileName = GetModuleFileName(
                         NULL, 
                         szPath, 
                         MAX_PATH);
   if (0 == dwGetModuleFileName)
   {
     cout << "Service Installation Failed "<< endl;
     cout << "Error No = " << GetLastError() << endl;
    }
   else
    {
     cout << "Successfully install the File\n" << endl;
    }// if

   //STEP-2 -> Open the Service Control Manager
    hScOpenSCManager = OpenSCManager(
                  NULL,//Local Machine
                  NULL,//By default Database i.e. SERVICES_ACTIVE_DATABASE
                  SC_MANAGER_ALL_ACCESS);//Access Right
   if (NULL == hScOpenSCManager)
   {
       cout << "OpenSCManager Failed "<< endl;
       cout << "Error No - " << GetLastError() << endl;
   }
   else
   {
    cout << "OpenSCManager Success" << endl;
   }

  //STEP-3 -> Create the Service
   hScCreateService = CreateService(
                    hScOpenSCManager,//SCM Handle
                    SERVICE_NAME,//Service Name
                    SERVICE_NAME,//Display Name
                    SERVICE_ALL_ACCESS,//Access Right
                    SERVICE_WIN32_OWN_PROCESS,//Service Type
                    SERVICE_DEMAND_START,//Service Start Type
                    SERVICE_ERROR_NORMAL,//Service Error Code
                    szPath,//Service Path
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL);
    if (NULL == hScCreateService)
    {
      cout << "CreateService Failed " << endl;
      cout << "Error No - " << GetLastError() << endl;
      CloseServiceHandle(hScOpenSCManager);
    }
    else
    {
       cout << "CreateService Success" << endl;
    }
   /*STEP-4 -> Close the Handle for OpenSCManager 
    and Create Service*/
    CloseServiceHandle(hScCreateService);
    CloseServiceHandle(hScOpenSCManager);

    cout << "ServiceInstall End" << endl;
 } //--End of ServiceInstall Definition--------//

//------ServiceDelete Definition--------//
void ServiceDelete(void)
{
   cout << "ServiceDelete Start" << endl;
   // Local Variable Definitions
   SC_HANDLE hScOpenSCManager = NULL;
   SC_HANDLE hScOpenService = NULL;
   BOOL bDeleteService = FALSE;
   //STEP-1 -> Open the Service Control Manager
   hScOpenSCManager = OpenSCManager(
                      NULL,
                      NULL,
                      SC_MANAGER_ALL_ACCESS);
   if (NULL == hScOpenSCManager)
   {
     cout << "OpenSCManager Failed "<< endl;
     cout << "Error No - " << GetLastError() << endl;
   }
  else
  {
    cout << "OpenSCManager Success" << endl;
   }
   //STEP-2 -> Open the Service
   hScOpenService = OpenService(
                    hScOpenSCManager,
                    SERVICE_NAME,
                    SERVICE_ALL_ACCESS);
   if (NULL == hScOpenService)
   {
     cout << "OpenService Failed " << endl;
     cout << "Error No- " << GetLastError() << endl;
    }
   else
   {
     cout << "OpenService Success " << endl;
   }
   //STEP-3 -> Delete Service
    bDeleteService = DeleteService(hScOpenService);
    if (FALSE == bDeleteService)
    {
      cout << "Delete Service Failed " << endl;
      cout << "Error No- " << GetLastError() << endl;
    }
    else
   {
     cout << "Delete Service Success" << endl;
    }

   /*STEP-4 -> Close the Handle for 
    SCM and OpenService */
   CloseServiceHandle(hScOpenService);
   CloseServiceHandle(hScOpenSCManager);
   cout << "ServiceDelete End" << endl;
  }
//---End of ServiceDelete Function-------------//












/*CopyRight reserved to awinsyspro.com 2019-2020
Sample Code for Windows Service- Part5 only */

//----ServiceStart Definitions-----//
void ServiceStart(void)
{
  cout << "Inside ServiceStart function" << endl;
  // Local Variable Definitions
  BOOL bStartService = FALSE;
  SERVICE_STATUS_PROCESS SvcStatusProcess;
  SC_HANDLE hOpenSCManager = NULL;
  SC_HANDLE hOpenService = NULL;
  BOOL bQueryServiceStatus = FALSE;
  DWORD dwBytesNeeded;
 //STEP-1-> Open Service Control Manager
  hOpenSCManager = OpenSCManager(
                   NULL,
                   NULL,
                   SC_MANAGER_ALL_ACCESS);
  if (NULL == hOpenSCManager)
  {
    cout << "hOpenSCManager Failed "<< endl;
    cout << "Error No = " << GetLastError() << endl;
  }
 else
 {
   cout << "hOpenSCManager Success" << endl;
  }
 //STEP-2 OpenService
 hOpenService = OpenService(
                hOpenSCManager,
                SERVICE_NAME,
                SC_MANAGER_ALL_ACCESS);
  if (NULL == hOpenService)
  {
   cout << "OpenService Failed "<< endl;
   cout << "Error No = " << GetLastError() << endl;
   CloseServiceHandle(hOpenSCManager);
  }
  else
  {
   cout << "OpenService Success" << endl;
  }
 //STEP-3->Query about current Service Status
 bQueryServiceStatus = QueryServiceStatusEx(
                    hOpenService,
                    SC_STATUS_PROCESS_INFO,
                   (LPBYTE)&SvcStatusProcess,
                    sizeof(SERVICE_STATUS_PROCESS),
                    &dwBytesNeeded);

 if (FALSE == bQueryServiceStatus)
 {
   cout << "QueryService Failed "<< endl;
   cout << "Error No = " << GetLastError() << endl;
  }
 else
  {
  cout << "QueryService Success" << endl;
  }
//STEP-4 -> Checked Service is running or stopped
if ((SvcStatusProcess.dwCurrentState != SERVICE_STOPPED) &&
(SvcStatusProcess.dwCurrentState != SERVICE_STOP_PENDING))
{
  cout << " service is already running" << endl;
}
else
{
  cout << "Service is Already Stopped" << endl;
}
//STEP-5 -> If Service is stopped Then query the service
 while(SvcStatusProcess.dwCurrentState == SERVICE_STOP_PENDING)
 {

  bQueryServiceStatus = QueryServiceStatusEx(
                     hOpenService,
                     SC_STATUS_PROCESS_INFO,
                    (LPBYTE)&SvcStatusProcess,
                    sizeof(SERVICE_STATUS_PROCESS),
                    &dwBytesNeeded);

  if (FALSE == bQueryServiceStatus)
  {
   cout << "QueryService Failed"<< endl;
   cout << "Error No = " << GetLastError() << endl;
   CloseServiceHandle(hOpenService);
   CloseServiceHandle(hOpenSCManager);
  }
  else
  {
   cout << "QueryService Success" << endl;
  }

}// while

 //STEP-6 -> Start The Service
   bStartService = StartService(
                   hOpenService,
                   NULL,
                   NULL);
  if (FALSE == bStartService)
  {
   cout << "StartService Failed "<< endl;
   cout << "Error No = " << GetLastError() << endl;
   CloseServiceHandle(hOpenService);
   CloseServiceHandle(hOpenSCManager);
  }
  else
  {
   cout << "StartService Success" << endl;
  }
 //STEP-7 -> Query the service again
 bQueryServiceStatus = QueryServiceStatusEx(
               hOpenService,
               SC_STATUS_PROCESS_INFO,
              (LPBYTE)&SvcStatusProcess,
              sizeof(SERVICE_STATUS_PROCESS),
              &dwBytesNeeded);

  if (FALSE == bQueryServiceStatus)
  {
    cout << "QueryService Failed "<< endl;
    cout << "Error No = " << GetLastError() << endl;
    CloseServiceHandle(hOpenService);
    CloseServiceHandle(hOpenSCManager);
  }
  else
  {
   cout << "QueryService Success" << endl;
  }
 // STEP-8 -> Check Service is running or not

 if(SvcStatusProcess.dwCurrentState == SERVICE_RUNNING)
 {
  cout << "Service Started Running..." << endl;
 }
 else
 {
  cout << "Service Running Failed"<< endl;
  cout << "Error No = " << GetLastError() << endl;
  CloseServiceHandle(hOpenService);
  CloseServiceHandle(hOpenSCManager);
 }
 /*STEP-9-> Close the Service Handle for 
  OpenSCManager & OpenService*/
 CloseServiceHandle(hOpenService);
 CloseServiceHandle(hOpenSCManager);
 cout << "ServiceStart end" << endl;
}//--End of ServiceStart fun definition-------//

//-----ServiceStop Definitions----------//
void ServiceStop(void)
{
  cout << "Inside Service Stop" << endl;
  //Local Variable Definitions
  SERVICE_STATUS_PROCESS SvcStatusProcess;
  SC_HANDLE hScOpenSCManager = NULL;
  SC_HANDLE hScOpenService = NULL;
  BOOL bQueryServiceStatus = TRUE;
  BOOL bControlService = TRUE;
  DWORD dwBytesNeeded;
  //STEP-1 -> Open Service Control Manager
  hScOpenSCManager = OpenSCManager(
                      NULL,
                      NULL,
                      SC_MANAGER_ALL_ACCESS);
  if (NULL == hScOpenSCManager)
  {
   cout << "OpenSCManager Failed "<< endl;
   cout << "Error No = " << GetLastError() << endl;
  }
  else
  {
    cout << "OpenSCManager Success" << endl;
  }// if
 //STEP-2 ->Open your Service
  hScOpenService = OpenService(
                 hScOpenSCManager,
                 SERVICE_NAME,
                 SC_MANAGER_ALL_ACCESS);
  if (NULL == hScOpenService)
  {
   cout << "OpenService Failed "<< endl;
   cout << "Error No = " << GetLastError() << endl;
   CloseServiceHandle(hScOpenSCManager);
   }
  else
  {
   cout << "OpenService Success" << endl;
  }// if

  //STEP-3 -> QueryServiceStatus

  bQueryServiceStatus = QueryServiceStatusEx(
                   hScOpenService,
                   SC_STATUS_PROCESS_INFO,
                   (LPBYTE)&SvcStatusProcess,
                   sizeof(SERVICE_STATUS_PROCESS),
                   &dwBytesNeeded);
  if (FALSE == bQueryServiceStatus)
  {
    cout << "QueryService Failed "<< endl;
    cout << "Error No = " <<GetLastError()<<endl;
    CloseServiceHandle(hScOpenService);
    CloseServiceHandle(hScOpenSCManager);
  }
  else
  {
   cout << "QueryService Success" << endl;
  }
  /*STEP-4 -> send a stop code to the 
   Service Control Manager*/
  bControlService = ControlService(
              hScOpenService,
              SERVICE_CONTROL_STOP,
              (LPSERVICE_STATUS)&SvcStatusProcess);
  if (TRUE == bControlService)
  {
    cout << "Control Service Success" << endl;
  }
  else
  {
    cout << "Control Service Failed "<< endl;
    cout << "Error No = " << GetLastError() << endl;
    CloseServiceHandle(hScOpenService);
    CloseServiceHandle(hScOpenSCManager);
   }// if

//STEP-5 -> wait for Service to stop
while (SvcStatusProcess.dwCurrentState != SERVICE_STOPPED)
{
  //STEP-6 -> Inside While Loop Query the service
  bQueryServiceStatus = QueryServiceStatusEx(
                 hScOpenService,
                 SC_STATUS_PROCESS_INFO,
                (LPBYTE)&SvcStatusProcess,
                 sizeof(SERVICE_STATUS_PROCESS),
                 &dwBytesNeeded);

  if (TRUE == bQueryServiceStatus)
  {
    cout << "QueryService Failed"<< endl;
    cout << "Error No = "<<GetLastError()<< endl;
    CloseServiceHandle(hScOpenService);
    CloseServiceHandle(hScOpenSCManager);
  }
  else
  {
    cout << "QueryService Success" << endl;
  }
  /*STEP-7 -> Inside While Loop, Check the 
  current state of Service*/
  if (SvcStatusProcess.dwCurrentState == SERVICE_STOPPED)
  {
    cout << "Service Stopped Successfully" << endl;
    break;// Coming out from While loop
  }
  else
  {
    cout << "Service Stopped Failed"<< endl;
    cout << "Error No = " << GetLastError() << endl;
    CloseServiceHandle(hScOpenService);
    CloseServiceHandle(hScOpenSCManager);
   }
}// while
  //STEP-8 -> Close the handle for Open SCM & Open Service 
  CloseServiceHandle(hScOpenService);
  CloseServiceHandle(hScOpenSCManager);
  cout << "Service Stop" << endl;
}//--End of ServiceStop Function Definition----//