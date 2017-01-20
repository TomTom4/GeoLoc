IMPLEMENTATION Standard {

    OS OurOS {
        STATUS = STANDARD;
        STARTUPHOOK = TRUE;
        ERRORHOOK = TRUE;
        SHUTDOWNHOOK = TRUE;
        PRETASKHOOK = FALSE;
        POSTTASKHOOK = FALSE;
        USEGETSERVICEID = FALSE;
        USEPARAMETERACCESS = FALSE;
        USERESSCHEDULER = TRUE;
    };


    TASK OurTask {
        PRIORITY = 1;
        SCHEDULE = NON;         // preemptability
        ACTIVATION = 1;
        AUTOSTART = TRUE {
            APPMODE = AppMode1;
            APPMODE = AppMode2;
        };
        RESOURCE = resource1;
        RESOURCE = resource2;
        RESOURCE = resource3;
        EVENT = event1;
        EVENT = event2;
        MESSAGE = anyMesssage1;
    };

    //No filter needed. No notification.

    MESSAGE actionneurA3 {
        MESSAGEPROPERTY = SEND_STATIC_EXTERNAL {
            CDATATYPE = "char";                         // 1 byte needed only
            TRANSFERPROPERTY = TRIGGERED;               // on veut envoyer l'ipdu immediatement.
            NETWORKMESSAGE = NWM_actionneurA3;
            INITIALVALUE = 0x00;                        // 0x00 as INITIALVALUE
        };
    };

    NETWORKMESSAGE NWM_actionneurA3 {
        IPDU = IPDU_actionneurA3;                          // Link to IPDU
        MESSAGEPROPERTY = STATIC {
            SIZEINBITS = 8;
            BITORDERING = BIGENDIAN;
            BITPOSITION = 0;                            // 8 ? avec BIGENDIAN
            DATAINTERPRETATION = UNSIGNEDINTEGER;
            INITIALVALUE = 0x00;
            DIRECTION = SENT {
                TRANSFERPROPERTY = TRIGGERED;           // TRIGGERED = immediatement
            };
        };
    };

    IPDU IPDU_actionneurA3 {
        SIZEINBITS = 16;
        IPDUPROPERTY = SENT {
            TIMEOUT = 250;
            FIRSTTIMEOUT = 100;
        };
        IPDUCALLOUT = "";               //pre-traitement
        LAYERUSED = "network";          // reseau
    };

    MESSAGE capteurC2 {
        MESSAGEPROPERTY = RECEIVE_UNQUEUED_EXTERNAL {               //unqueued needed
            CDATATYPE = "char";
            LINK = FALSE {                                                  // No task, link to a function.
                NETWORKMESSAGE = NWM_capteurC2;
                NETWORKORDERCALLOUT = "calculCommandeValeurActionneur";
            };
        };
    };

    NETWORKMESSAGE NWM_capteurC2 {
        IPDU = IPDU_capteurC2;                          // Link to IPDU
        MESSAGEPROPERTY = STATIC {
            SIZEINBITS = 8;
            BITORDERING = BIGENDIAN;
            BITPOSITION = 8;                            // 8 ? avec BIGENDIAN
            DATAINTERPRETATION = UNSIGNEDINTEGER;
            INITIALVALUE = 0x00;
            DIRECTION = SENT {
                TRANSFERPROPERTY = TRIGGERED;           // TRIGGERED = immediatement
            };
        };
    };

    IPDU IPDU_capteurC2 {
        SIZEINBITS = 16;
        IPDUPROPERTY = SENT {
            TRANSMISSIONMODE = DIRECT;
            TIMEOUT = 250;
        };
        IPDUCALLOUT = "";
        LAYERUSED = "network";
    };


    MESSAGE capteurC3 {
        MESSAGEPROPERTY = RECEIVE_QUEUED_EXTERNAL {
            CDATATYPE = "char";
            LINK = FALSE {                                                  // No task, link to a function.
                NETWORKMESSAGE = NWM_calculCommandeValeurActionneur;
                NETWORKORDERCALLOUT = "calculCommandeValeurActionneur";
            };
        };
    };


    MESSAGE capteurC4 {
        MESSAGEPROPERTY = RECEIVE_QUEUED_EXTERNAL {
            CDATATYPE = "char";
            LINK = FALSE {                                                  // No task, link to a function.
                NETWORKMESSAGE = NWM_calculCommandeValeurActionneur;
                NETWORKORDERCALLOUT = "calculCommandeValeurActionneur";
            };
        };
    };
};
