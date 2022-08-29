//    Copyright (C) 2014 Sascha Ittner <sascha.ittner@modusoft.de>
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
/*
Linuxcnc-ethercat typedef;
hal_type_t    ;
hal_float_t   ;
hal_s32_t     ;
hal_u32_t     ;
hal_bit_t     ;
uint32_t      ;
uint16_t      ;
uint8_t       ;
size_t        ;
ec_direction_t;
ec_al_state_t ;
*/
/* Master 0, Slave 0, "EasyCAT 32+32 rev 1"
 * Vendor ID:       0x0000079a
 * Product code:    0x00defede
 * Revision number: 0x00005a01
*/

#include "lcec.h"
#include "lcec_easycat.h"

typedef struct 
{
	hal_float_t *ByteFromSlave;		    // To Slave     HAL_OUT
	hal_float_t *ByteToSlave  ;		    // From Slave   HAL_IN 

  unsigned int off_ByteFromSlave;   // read from Slave
  unsigned int off_ByteToSlave;     // write to Slave

	hal_float_t *enc00scale;        //parameter   HAL_RW
  hal_float_t *enc01scale;        //parameter   HAL_RW
} lcec_easycat_data_t;
 
static const lcec_pindesc_t slave_pins[] = 
{
	{ HAL_FLOAT, HAL_IN, 	offsetof(lcec_easycat_data_t, ByteToSlave), "%s.%s.%s.ByteToSlave" },
	{ HAL_FLOAT, HAL_OUT, offsetof(lcec_easycat_data_t, ByteFromSlave), "%s.%s.%s.ByteFromSlave" },  
  { HAL_TYPE_UNSPECIFIED, HAL_DIR_UNSPECIFIED, -1, NULL }
};

static const lcec_pindesc_t slave_params[] = 
{
	{ HAL_FLOAT, HAL_RW, 	offsetof(lcec_easycat_data_t, enc00scale), "%s.%s.%s.enc00scale" },
	{ HAL_FLOAT, HAL_RW, 	offsetof(lcec_easycat_data_t, enc01scale), "%s.%s.%s.enc01scale" },
	{ HAL_TYPE_UNSPECIFIED, HAL_DIR_UNSPECIFIED, -1, NULL }
};

static ec_pdo_entry_info_t lcec_easycat_pdo_entries[] = 
{
    {0x0005, 0x01, 8}, /* Byte0     Read from a Slave Value // SO: It's a Slave OUTPUT */
    {0x0005, 0x02, 8}, /* Byte1 */
    {0x0005, 0x03, 8}, /* Byte2 */
    {0x0005, 0x04, 8}, /* Byte3 */
    {0x0005, 0x05, 8}, /* Byte4 */
    {0x0005, 0x06, 8}, /* Byte5 */
    {0x0005, 0x07, 8}, /* Byte6 */
    {0x0005, 0x08, 8}, /* Byte7 */
    {0x0005, 0x09, 8}, /* Byte8 */
    {0x0005, 0x0a, 8}, /* Byte9 */
    {0x0005, 0x0b, 8}, /* Byte10 */
    {0x0005, 0x0c, 8}, /* Byte11 */
    {0x0005, 0x0d, 8}, /* Byte12 */
    {0x0005, 0x0e, 8}, /* Byte13 */
    {0x0005, 0x0f, 8}, /* Byte14 */
    {0x0005, 0x10, 8}, /* Byte15 */
    {0x0005, 0x11, 8}, /* Byte16 */
    {0x0005, 0x12, 8}, /* Byte17 */
    {0x0005, 0x13, 8}, /* Byte18 */
    {0x0005, 0x14, 8}, /* Byte19 */
    {0x0005, 0x15, 8}, /* Byte20 */
    {0x0005, 0x16, 8}, /* Byte21 */
    {0x0005, 0x17, 8}, /* Byte22 */
    {0x0005, 0x18, 8}, /* Byte23 */
    {0x0005, 0x19, 8}, /* Byte24 */
    {0x0005, 0x1a, 8}, /* Byte25 */
    {0x0005, 0x1b, 8}, /* Byte26 */
    {0x0005, 0x1c, 8}, /* Byte27 */
    {0x0005, 0x1d, 8}, /* Byte28 */
    {0x0005, 0x1e, 8}, /* Byte29 */
    {0x0005, 0x1f, 8}, /* Byte30 */
    {0x0005, 0x20, 8}, /* Byte31 */
    {0x0006, 0x01, 8}, /* Byte0     Wite a Value OnTo a Slave // SO: It's a Slaves INPUT */
    {0x0006, 0x02, 8}, /* Byte1 */
    {0x0006, 0x03, 8}, /* Byte2 */
    {0x0006, 0x04, 8}, /* Byte3 */
    {0x0006, 0x05, 8}, /* Byte4 */
    {0x0006, 0x06, 8}, /* Byte5 */
    {0x0006, 0x07, 8}, /* Byte6 */
    {0x0006, 0x08, 8}, /* Byte7 */
    {0x0006, 0x09, 8}, /* Byte8 */
    {0x0006, 0x0a, 8}, /* Byte9 */
    {0x0006, 0x0b, 8}, /* Byte10 */
    {0x0006, 0x0c, 8}, /* Byte11 */
    {0x0006, 0x0d, 8}, /* Byte12 */
    {0x0006, 0x0e, 8}, /* Byte13 */
    {0x0006, 0x0f, 8}, /* Byte14 */
    {0x0006, 0x10, 8}, /* Byte15 */
    {0x0006, 0x11, 8}, /* Byte16 */
    {0x0006, 0x12, 8}, /* Byte17 */
    {0x0006, 0x13, 8}, /* Byte18 */
    {0x0006, 0x14, 8}, /* Byte19 */
    {0x0006, 0x15, 8}, /* Byte20 */
    {0x0006, 0x16, 8}, /* Byte21 */
    {0x0006, 0x17, 8}, /* Byte22 */
    {0x0006, 0x18, 8}, /* Byte23 */
    {0x0006, 0x19, 8}, /* Byte24 */
    {0x0006, 0x1a, 8}, /* Byte25 */
    {0x0006, 0x1b, 8}, /* Byte26 */
    {0x0006, 0x1c, 8}, /* Byte27 */
    {0x0006, 0x1d, 8}, /* Byte28 */
    {0x0006, 0x1e, 8}, /* Byte29 */
    {0x0006, 0x1f, 8}, /* Byte30 */
    {0x0006, 0x20, 8}, /* Byte31 */
};

static ec_pdo_info_t lcec_easycat_pdos[] = 
{
  	// OUTPUTS_READ 0x0006  ByteFromSlave
    {0x1600,  32, lcec_easycat_pdo_entries + 0 },   /* 32 Bytes Outputs */
    //INPUTS_WRITE  0x0005  ByteToSlave
    {0x1a00,  32, lcec_easycat_pdo_entries + 32 },   /* 32 Bytes Inputs  */

};

static ec_sync_info_t lcec_easycat_syncs[] = 
{
	{ 0, EC_DIR_OUTPUT, 1, lcec_easycat_pdos + 0, EC_WD_ENABLE },
	{ 1, EC_DIR_INPUT,  1, lcec_easycat_pdos + 1, EC_WD_DISABLE },
	{ 0xff }
};

void lcec_easycat_read	(struct lcec_slave *slave, long period);
void lcec_easycat_write	(struct lcec_slave *slave, long period);

//static int32_t	ByteToSlave_00  [32];
//static int32_t	ByteFromSlave_00[32];

int lcec_easycat_init(int comp_id, struct lcec_slave *slave, ec_pdo_entry_reg_t *pdo_entry_regs) 
{
  lcec_master_t *master = slave->master;
  lcec_easycat_data_t *hal_data;
  int err;

  // initialize callbacks
  slave->proc_read = lcec_easycat_read;
  slave->proc_write = lcec_easycat_write;

  // alloc hal memory
  if ((hal_data = hal_malloc(sizeof(lcec_easycat_data_t))) == NULL) {
    rtapi_print_msg(RTAPI_MSG_ERR, LCEC_MSG_PFX "hal_malloc() for slave %s.%s failed\n", master->name, slave->name);
    return -EIO;
  }
  memset(hal_data, 0, sizeof(lcec_easycat_data_t));
  slave->hal_data = hal_data;

  // initializer sync info
  slave->sync_info = lcec_easycat_syncs;

// initialize PDO entries
//  WRITE  To EasyCat   HAL_IN_PIN
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x0005, 0x01, &hal_data->off_ByteToSlave ,    NULL);

//  READ  From  EasyCat   HAL_OUT_PIN
  LCEC_PDO_INIT(pdo_entry_regs, slave->index, slave->vid, slave->pid, 0x0006, 0x01, &hal_data->off_ByteFromSlave ,    NULL);
  
  // export pins
  if ((err = lcec_pin_newf_list(hal_data, slave_pins, LCEC_MODULE_NAME, master->name, slave->name)) != 0) 
  {
	  return err;
  }

  // export parameters
  if ((err = lcec_param_newf_list(hal_data, slave_params, LCEC_MODULE_NAME, master->name, slave->name)) != 0) 
  {
	  return err;
  }

// initialize variables
//	hal_data->ByteToSlave     = 	0;  
//  hal_data->ByteFromSlave   = 	0;
  
return 0;
}

void lcec_easycat_read(struct lcec_slave *slave, long period) 
{
  lcec_master_t *master = slave->master;
  lcec_easycat_data_t *hal_data = (lcec_easycat_data_t *) slave->hal_data;
  uint8_t *pd = master->process_data;  

  uint8_t	BytesRead[32];

//  BytesRead[0] = EC_READ_U8(&pd[hal_data->off_ByteFromSlave]);
//  *(hal_data->ByteFromSlave) =  BytesRead[0];

  *(hal_data->ByteFromSlave) =  EC_READ_U8(&pd[hal_data->off_ByteFromSlave]);

}

void lcec_easycat_write(struct lcec_slave *slave, long period)
{
  lcec_master_t *master = slave->master;
  lcec_easycat_data_t *hal_data = (lcec_easycat_data_t *) slave->hal_data;
  uint8_t *pd = master->process_data; 

  uint8_t fValue;

  fValue = *(hal_data->ByteToSlave);
  for(int i=0; i<32; i++)
    EC_WRITE_U8(&pd[hal_data->off_ByteToSlave +i], fValue);

//  EC_WRITE_U8(&pd[hal_data->off_ByteToSlave], *(hal_data->ByteToSlave));
}





