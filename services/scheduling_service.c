/* 
 * File:   scheduling_service.c
 * Author: 
 *
 * Created on March 8, 2016, 9:05 PM
 * This is the implementation of scheduling service as is
 * documented at pages 99-118 of ECSS-E-70-41A document.
 * Service Type 11 
 * (some restrictions apply)
 */

#include "scheduling_service.h"

uint8_t find_schedule_pos();

SC_pkt scheduling_mem_array[SC_MAX_STORED_SCHEDULES];
Scheduling_service_state sc_s_state;


/*  Initiates the scheduling service.
 *  Loads the schedules from persistent storage.
 */
SAT_returnState load_schedules()
{
    SC_pkt sp1,sp2,sp3,sp4;
    
    sp1.num_of_sch_tc=1;
    sp1.intrlck_set_id=0;
    sp1.intrlck_ass_id=0;
    sp1.assmnt_type = 1;
    sp1.release_time = 5;
    sp1.timeout = 0;
    sp1.enabled = 1;
    
    sp2.num_of_sch_tc=1;
    sp2.intrlck_set_id=0;
    sp2.intrlck_ass_id=0;
    sp2.assmnt_type = 1;
    sp2.release_time = 10;
    sp2.timeout = 0;
    sp2.enabled = 1;
    
    sp3.num_of_sch_tc=1;
    sp3.intrlck_set_id=0;
    sp3.intrlck_ass_id=0;
    sp3.assmnt_type = 1;
    sp3.release_time = 15;
    sp3.timeout = 0;
    sp3.enabled = 1;
    
    sp4.num_of_sch_tc=1;
    sp4.intrlck_set_id=0;
    sp4.intrlck_ass_id=0;
    sp4.assmnt_type = 1;
    sp4.release_time = 20;
    sp4.timeout = 0;
    sp4.enabled = 1;
    
    scheduling_insert_api(&sp1);
    scheduling_insert_api(&sp2);
    scheduling_insert_api(&sp3);
    scheduling_insert_api(&sp4);
}

void cross_schedules(){
    
    for ( int o=0;o<SC_MAX_STORED_SCHEDULES;o++){
//        if (mem_sche[o].time <= seconds ){

//        }
    }
}

/*
 *
 */
SAT_returnState init_schedules(){   
    
    load_schedules();
        time_t current_time;

        /* Cross schedules array, 
         * in every pass check if the specific schedule 
         * if enabled,
         *      if it is then check if its relative or absolute and check the time.
         *      if time >= release time, then execute it. (?? what if time has passed?)
         * else !enabled
         *      if time>= release time, then mark it as !valid
         */
        
        while(1){
//        /* Obtain current time. */
//        current_time = time(NULL);
//
//        if (current_time == ((time_t)-1))
//        {
////            printf(stderr, "Failure to obtain the current time.\n");
////            exit(EXIT_FAILURE);
//        }
//
//        /* Convert to local time format. */
//        c_time_string = ctime(&current_time);
//
//        if (c_time_string == NULL)
//        {
////            printf(stderr, "Failure to convert the current time.\n");
////            exit(EXIT_FAILURE);
//        }
//        HAL_UART_Transmit(&Uart2Handle, (uint8_t *)c_time_string, 25,5000);
//        /* Print to stdout. ctime() has already added a terminating newline character. */
////         printf("%s", c_time_string);
////        exit(EXIT_SUCCESS);
//        
////        if ( scheduling_stateAPI() ){
////            cross_schedules();
////        }
         HAL_Delay(100);
    }
}

SAT_returnState scheduling_app(tc_tm_pkt* spacket){
    
    /*TODO: add assertions*/
    SC_pkt the_sc_packet;
    uint32_t time;
    uint16_t exec_timeout;
    /*extract the scheduling packet from the data pointer*/
    
    the_sc_packet.sub_schedule_id = spacket->data[0];
    the_sc_packet.num_of_sch_tc = spacket->data[1];
    the_sc_packet.intrlck_set_id = spacket->data[2];
    the_sc_packet.intrlck_ass_id = spacket->data[3];
    the_sc_packet.assmnt_type = spacket->data[4];
    the_sc_packet.sch_evt = spacket->data[5];
//    6789 is the time fields
    time = spacket->data[6] << 23 | spacket->data[7] | spacket->data[8] | spacket->data[9];
    exec_timeout = spacket->data[10] << 7 | spacket->data[11];
    
    /*TODO: parse the rest telecommand packet to extract needed info for scheduling packet*/
    
//    scheduling_insert_api(mem_schedule, &the_sc_packet);
     scheduling_insert_api(&the_sc_packet);
    
    return SATR_OK;
}

SAT_returnState scheduling_insert_api( /*SC_pkt* sch_mem_pool, */
                                       SC_pkt* theSchpck ){        
    
    /*check if schedule array is already full*/
    
    if ( !C_ASSERT(sc_s_state.schedule_arr_full) == true ){  
        /*TODO: Here to create a telemetry/log saying "I'm full"*/
        return SATR_SCHEDULE_FULL;
    }
    
    uint8_t pos = find_schedule_pos(scheduling_mem_array);
    if ( !C_ASSERT(pos != SC_MAX_STORED_SCHEDULES) == true){
        return SATR_SCHEDULE_FULL;
    }
    
    /*Check sub-schedule id*/
    if ( !C_ASSERT(theSchpck->sub_schedule_id !=1) == true ){
        return SATR_SSCH_ID_INVALID;
    }
    /*Check number of tc in schpck id*/
    if ( !C_ASSERT(theSchpck->num_of_sch_tc !=1) == true ){
        return SATR_NMR_OF_TC_INVALID;
    }
    /*Check interlock set id*/
    if ( !C_ASSERT(theSchpck->intrlck_set_id !=0) == true){
        return SATR_INTRL_ID_INVALID;
    }
    /*Check interlock assessment id*/
    if ( !C_ASSERT(theSchpck->intrlck_ass_id !=1) == true ){
        return SATR_ASS_INTRL_ID_INVALID;
    }
//    /*Check release time type id*/
//    if ( (!C_ASSERT(theSchpck->sch_evt != ABSOLUTE) == true) ||
//         (!C_ASSERT(theSchpck->sch_evt != QB50EPC) == true) ){
//        return SATR_RLS_TIMET_ID_INVALID;
//    }
    /*Check time value*/
//    if (   ){
//        return TIME_SPEC_INVALID;
//    }
    /*Check execution time out*/
//    if (  ){
//       return INTRL_LOGIC_ERROR; 
//    }
        
    /*Copy the packet into the array*/
    scheduling_mem_array[pos] = *theSchpck;
    sc_s_state.nmbr_of_ld_sched++;
    if ( sc_s_state.nmbr_of_ld_sched == SC_MAX_STORED_SCHEDULES ){
        /*schedule array has become full*/
        sc_s_state.schedule_arr_full = true;
        /*TODO: turn 1, 0 to true, false*/
    }
    return SATR_OK;
}

SAT_returnState scheduling_state_api(){

    return (scheduling_enabled ? SATR_OK : SATR_SCHEDULE_DISABLED);
}

SAT_returnState scheduling_remove_schedule_api( SC_pkt* sch_mem_pool, 
                                                SC_pkt* theSchpck, uint8_t apid, uint16_t seqc ){
    
    uint8_t pos = 0;
    while( pos<SC_MAX_STORED_SCHEDULES ){
        if (sch_mem_pool[pos].app_id == apid && sch_mem_pool[pos].seq_count == seqc){
            sch_mem_pool[pos].valid = 0;
            sc_s_state.nmbr_of_ld_sched--;
            sc_s_state.schedule_arr_full = 0;
        }
        pos++;
    }
    return SATR_OK;
} 

SAT_returnState scheduling_reset_schedule_api(SC_pkt* sch_mem_pool){
    uint8_t pos = 0;
    while( pos<SC_MAX_STORED_SCHEDULES ){
        sch_mem_pool[pos++].valid = false;
    }
    return SATR_OK;
}

SAT_returnState scheduling_time_shift_all_schedules_api(SC_pkt* sch_mem_pool, int32_t secs ){
    
    uint8_t pos = 0;
    while( pos<SC_MAX_STORED_SCHEDULES ){
        if (sch_mem_pool[pos].sch_evt == ABSOLUTE ){
            /*convert the secs to utc and add them or remove them from the time field.*/
            
            /*TODO: timing api*/
        }
        else
        if(sch_mem_pool[pos].sch_evt == QB50EPC ){
            /*add them or remove them from the time field. Error if */
            
            /*TODO: timing api*/
        }
    }
    return SATR_OK;
}

/* Time shifts selected Schedule_pcks on the Schedule 
 * * Service Subtype 7
 */
SAT_returnState time_shift_sel_schedule(SC_pkt* sch_mem_pool, uint8_t apid, uint16_t seqcount ){
    
    uint8_t pos = 0;
    while( pos<SC_MAX_STORED_SCHEDULES ){
//        if( sch_mem_pool[pos].app_id == apid && 
//            sch_mem_pool[pos].seq_count == seqcount)
//        {
//            /*this is the schedule to be timeshifted. shiftit*/
//            if (sch_mem_pool[pos].sch_evt == ABSOLUTE ){
//            /*convert the secs to utc and add them or remove them from the time field.*/
//            
//        }
//            else
//            if(sch_mem_pool[pos].sch_evt == QB50EPC ){
//                /*add them or remove them from the time field. Error if */
//            }
//        }
        pos++;
    }
    return SATR_OK;
}

/* Time shifts selected telecommands over a time period on the Schedule 
 * * Service Subtype 8
 */
SAT_returnState time_shift_sel_scheduleOTP( SC_pkt* theSchpck ){
    
    return SATR_OK;
}

/* Reports detailed info about every telecommand the Schedule 
 * * Service Subtype 16
 */
SAT_returnState report_detailed( SC_pkt theSchpck ){
    
    return SATR_OK;
}


/* Reports detailed info about a subset of telecommands from the Schedule 
 * * Service Subtype 9
 */
SAT_returnState report_detailed_subset( SC_pkt theSchpck ){
    
    return SATR_OK;
}

/* 
 * * Service Subtype 10
 *
OBC_returnStateTypedef report_( Schedule_pck theSchpck ){
    
    return R_OK;
}*/

/* Reports summary info of all telecommands from the Schedule 
 * * Service Subtype 17
 */
SAT_returnState report_summary_all( SC_pkt theSchpck ){
    
    return SATR_OK;
}

/* Reports summary info of a subset of telecommands from the Schedule 
 * * Service Subtype 12
 */
SAT_returnState report_summary_subset( SC_pkt theSchpck ){
    
    return SATR_OK;
}

/* Reports summary info of all telecommands from the Schedule 
 * * Service Subtype 
 *
OBC_returnStateTypedef ( Schedule_pck theSchpck ){
    
    return R_OK;
}*/

/* Find an index position in the Schedule_pck array to
 * insert the Scheduling packet.
 */
uint8_t find_schedule_pos(SC_pkt* sche_mem_pool)
{
    uint8_t pos=0;
    while( sche_mem_pool[pos].valid == true ){
      if (pos >= SC_MAX_STORED_SCHEDULES){ return SC_MAX_STORED_SCHEDULES; }
      else{ return pos; }
      pos++;
    }
    return pos; /*returns 0*/
}

