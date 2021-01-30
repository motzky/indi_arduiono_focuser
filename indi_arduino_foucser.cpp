#include "config.h"
#include "indi_arduino_foucser.h"

#include <memory>
#include <cstring>

static std::unique_ptr<ArduinoFcouser> myDriver(new ArduinoFcouser());

void ISGetProperties(const char* dev)
{
    myDriver->ISGetProperties(dev);
}

void ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n)
{
    myDriver->ISNewSwitch(dev, name, states, names, n);
}

void ISNewText(const char* dev, const char *name, char *texts[], char *names[], int n)
{
    myDriver->ISNewText(dev, name, texts, names, n);
}

void ISNewNumber(const char *dev, const char* name, double values[], char *names[], int n)
{
    myDriver->ISNewNumber(dev, name, values, names, n);
}

void ISNewBLOB(const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[], char *formats[], char *names[], int n)
{
    myDriver->ISNewBLOB(dev, name, sizes, blobsizes, blobs, formats, names, n);
}

void ISSnoopDevice(XMLEle *root)
{
    myDriver->ISSnoopDevice(root);
}

ArduinoFcouser::ArduinoFcouser()
{
    setVersion(CDRIVER_VERSION_MAJOR, CDRIVER_VERSION_MINOR);

    setSupportedConnections(CONNECTION_SERIAL);

    SetCapability(FOCUSER_CAN_ABS_MOVE | FOCUSER_CAN_REL_MOVE | FOCUSER_CAN_ABORT);
}

const char *ArduinoFcouser::getDefaultName()
{
    return "Arduino Focuser Driver";
}

bool ArduinoFcouser::initProperties() 
{
    INDI::Focuser::initProperties();

    addAuxControls();

    return true;
}

bool ArduinoFcouser::updateProperties()
{
    INDI::Focuser::updateProperties();

    if(isConnected())
    {
        // TODO: Call define* for any custom properties only visible when connected.
        return true;
    }

    // TODO: Call deleteProperty for any custom properties only visible when connected.

    return true;
}

void ArduinoFcouser::ISGetProperties(const char *dev) 
{
    INDI::Focuser::ISGetProperties(dev);

    // TODO: Call define* for any custom properties
}

bool ArduinoFcouser::ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n)
{
    if(dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        // TODO: Check to see if this is for any of my custom Number properties.
    }

    // Nobody has claimed this, so let the parent handle it
    return INDI::Focuser::ISNewNumber(dev, name, values, names, n);
}

bool ArduinoFcouser::ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n)
{
    // Make sure it is for us.
    if (dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        // TODO: Check to see if this is for any of my custom Switch properties.
    }

    // Nobody has claimed this, so let the parent handle it
    return INDI::Focuser::ISNewSwitch(dev, name, states, names, n);

}

bool ArduinoFcouser::ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n)
{
    // Make sure it is for us.
    if (dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        // TODO: Check to see if this is for any of my custom Text properties.
    }

    // Nobody has claimed this, so let the parent handle it
    return INDI::Focuser::ISNewText(dev, name, texts, names, n);
}

bool ArduinoFcouser::ISSnoopDevice(XMLEle *root) 
{
    // TODO: Check to see if this is for any of my custom Snoops. Fo shizzle.

    return INDI::Focuser::ISSnoopDevice(root);
}

void ArduinoFcouser::TimerHit() 
{
    if (!isConnected())
        return;

    // TODO: Poll your device if necessary. Otherwise delete this method and it's
    // declaration in the header file.

    LOG_INFO("timer hit");

    // If you don't call SetTimer, we'll never get called again, until we disconnect
    // and reconnect.
    SetTimer(POLLMS);
}

bool ArduinoFcouser::saveConfigItems(FILE *fp) 
{
    INDI::Focuser::saveConfigItems(fp);

    // TODO: Call IUSaveConfig* for any custom properties I want to save.

    return true;
}

bool ArduinoFcouser::Handshake()
{
    if (isSimulation())
    {
        LOGF_INFO("Connected successfuly to simulated %s.", getDeviceName());
        return true;
    }

    // NOTE: PortFD is set by the base class.

    // TODO: Any initial communciation needed with our focuser, we have an active
    // connection.

    return true;
}

IPState ArduinoFcouser::MoveFocuser(FocusDirection dir, int speed, uint16_t duration)
{
    // NOTE: This is needed if we don't specify FOCUSER_CAN_ABS_MOVE
    // TODO: Actual code to move the focuser. You can use IEAddTimer to do a
    // callback after "duration" to stop your focuser.
    LOGF_INFO("MoveFocuser: %d %d %d", dir, speed, duration);
    return IPS_OK;
}

IPState ArduinoFcouser::MoveAbsFocuser(uint32_t steps)
{
    // NOTE: This is needed if we do specify FOCUSER_CAN_ABS_MOVE
    // TODO: Actual code to move the focuser.
    LOGF_INFO("MoveAbsFocuser: %d", steps);
    return IPS_OK;
}

IPState ArduinoFcouser::MoveRelFocuser(FocusDirection dir, uint32_t ticks) 
{
    // NOTE: This is needed if we do specify FOCUSER_CAN_REL_MOVE
    // TODO: Actual code to move the focuser.
    LOGF_INFO("MoveRelFocuser: %d %d", dir, ticks);
    return IPS_OK;
}

bool ArduinoFcouser::AbortFocuser() 
{
    // NOTE: This is needed if we do specify FOCUSER_CAN_ABORT
    // TODO: Actual code to stop the focuser.
    LOG_INFO("AbortFocuser");
    return true;
}
