/*
 * EXTI_prv.h
 *
 *  Created on: May 26, 2023
 *      Author: Ahmed Gomaa
 */

#ifndef EXTI_PRV_H_
#define EXTI_PRV_H_

/************************************************************************************/
/*	To trigger interrupt you can choose from this options : 			     	*****/
/*  													1- RISING_EDGE			*****/
/* 														2- FALLING_EDGE			*****/
/* 														3- ON_CHANGE			*****/
/* 														4- LOW_LEVEL 			*****/
/* **********************************************************************************/

#define RISING_EDGE			1u
#define FALLING_EDGE		2u
#define ON_CHANGE			3u
#define LOW_LEVEL			4u


/************************************************************************************/
/*	To Enable or Disable any of interrupt sources you can choose from options: 	*****/
/*  													1- ENABLED   			*****/
/* 														2- DISABLED	    		*****/
/* **********************************************************************************/

#define ENABLED				1u
#define DISABLED			2u

#endif /* EXTI_PRV_H_ */
