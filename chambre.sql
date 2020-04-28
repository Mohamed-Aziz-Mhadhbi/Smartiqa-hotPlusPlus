--------------------------------------------------------
--  File created - Tuesday-April-28-2020   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table CHAMBRE
--------------------------------------------------------

  CREATE TABLE "LALOU"."CHAMBRE" 
   (	"NUM_CH" VARCHAR2(20 BYTE), 
	"TYPE" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
REM INSERTING into LALOU.CHAMBRE
SET DEFINE OFF;
Insert into LALOU.CHAMBRE (NUM_CH,TYPE) values ('255','chanbre');
Insert into LALOU.CHAMBRE (NUM_CH,TYPE) values ('658','chambre');
Insert into LALOU.CHAMBRE (NUM_CH,TYPE) values ('12','salle');
Insert into LALOU.CHAMBRE (NUM_CH,TYPE) values ('256','chambre');
Insert into LALOU.CHAMBRE (NUM_CH,TYPE) values ('529','suite');
Insert into LALOU.CHAMBRE (NUM_CH,TYPE) values ('25','salle');
Insert into LALOU.CHAMBRE (NUM_CH,TYPE) values ('22','salle');
Insert into LALOU.CHAMBRE (NUM_CH,TYPE) values ('659','suite');
Insert into LALOU.CHAMBRE (NUM_CH,TYPE) values ('234','salle');
--------------------------------------------------------
--  DDL for Index CHAMBRE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "LALOU"."CHAMBRE_PK" ON "LALOU"."CHAMBRE" ("NUM_CH") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  Constraints for Table CHAMBRE
--------------------------------------------------------

  ALTER TABLE "LALOU"."CHAMBRE" ADD CONSTRAINT "CHAMBRE_PK" PRIMARY KEY ("NUM_CH")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
  ALTER TABLE "LALOU"."CHAMBRE" MODIFY ("NUM_CH" NOT NULL ENABLE);
