﻿#ifndef PPU_H
#define PPU_H

#include <stdint.h>
#include <string.h>
#include "ppu_bus.h"

// 状态标志位
class PPUCTRL
{
public:
	uint8_t data;
	PPUCTRL() {
		data = 0; //
	}
	int getBasentable() const
	{ //
		return data & 3;
	}
	int getAddrincrement() const
	{ //
		if (data & (1 << 2)) return 32;
		else return 1;
	}
	bool getSptableDx() const
	{ //
		if (data & (1 << 3)) return 1;
		else return 0;
	}
	bool getBptableDx() const
	{ //
		if (data & (1 << 4)) return 1;
		else return 0;
	}
	bool getSpritesize() const
	{ //
		if (data & (1 << 5)) return 1;
		else return 0;
	}
	bool getNmi() const
	{ //
		if (data & (1 << 7)) return 1;
		else return 0;
	}
};

class PPUMASK
{
public:
	uint8_t data;
	PPUMASK() {
		data = 0;
	}
	bool get_greymode() { //
		if (data & 1) return 1;
		else return 0;
	}
	bool get_showedgebkg() { //
		if (data & (1 << 1)) return 1;
		else return 0;
	}
	bool get_showedgespr() { //
		if (data & (1 << 2)) return 1;
		else return 0;
	}
	bool get_showbkg() { //
		if (data & (1 << 3)) return 1;
		else return 0;
	}
	bool get_showspr() { //
		if (data & (1 << 4)) return 1;
		else return 0;
	}
};

class PPUSTATUS
{
public:
	uint8_t data;
	PPUSTATUS() {
		data = 0;
	}
	bool get_sproverflow() {
		if (data & (1 << 5)) return 1;
		else return 0;
	}
	bool get_spr0hit() {
		if (data & (1 << 6)) return 1;
		else return 0;
	}
	bool get_vblank() { //
		if (data & (1 << 7)) return 1;
		else return 0;
	}
	void set_sproverflow(bool n) {
		if (n) data |= 1 << 5;
		else data &= 0xdf;
	}
	void set_spr0hit(bool n) {
		if (n) data |= 1 << 6;
		else data &= 0xbf;
	}
	void set_vblank(bool n) { //
		if (n) data |= 1 << 7;
		else data &= 0x7f;
	}
};

class REG_V
{
public:
	uint16_t data;
	REG_V() {
		data = 0;
	}
	void set_low8(uint8_t data_in) { //
		data &= 0xff00;
		data |= data_in;
	}
	void set_hi6(uint8_t data_in) { //
		data &= 0x00ff;
		data |= ((data_in & 0x3f) << 8);
	}
	void set_nametable(uint8_t nametable_dx) { //
		data &= 0xf3ff;
		data |= ((nametable_dx & 0x3) << 10);
	}
	void set_nametable_x(bool nametable_x) { //
		if (nametable_x) data |= 1 << 10;
		else data &= 0xfbff;
	}
	void set_nametable_y(bool nametable_y) { //
		if (nametable_y) data |= 1 << 11;
		else data &= 0xf7ff;
	}
	void set_xscroll(uint8_t xscroll) { //
		data &= 0xffe0;
		data |= (xscroll & 0x1f);
	}
	void set_yscroll(uint8_t yscroll) { //
		data &= 0xfc1f;
		data |= ((yscroll & 0x1f) << 5);
	}
	void set_yfine(uint8_t yfine) { //
		data &= 0x8fff;
		data |= ((yfine & 0x7) << 12);
	}
	uint8_t get_xscroll() { //
		return data & 0x1f;
	}
	bool get_nametable_x() {
		if (data & (1 << 10)) return 1;
		else return 0;
	}
	bool get_nametable_y() {
		if (data & (1 << 11)) return 1;
		else return 0;
	}
	uint8_t get_yscroll() { //
		return (data & 0x3e0) >> 5;
	}
	uint8_t get_yfine() { //
		return (data & 0x7000) >> 12;
	}
};

class PPU2
{
public:
	//
	PPUCTRL reg_ctrl;
	PPUMASK reg_mask;
	PPUSTATUS reg_sta;
	uint8_t reg_oamaddr; //

	bool address_latch; //
	uint8_t xfine; //
	REG_V tmp_addr; //
	REG_V data_addr; //
	uint8_t data_buffer;
public:
	//
	void writeCtrl(uint8_t ctrl);
	void writeMask(uint8_t mask);
	uint8_t getStatus();
	void writeOamaddr(uint8_t addr);
	void writeOamdata(uint8_t data);
	uint8_t getOamdata();
	void writeScroll(uint8_t scroll);
	void writeAddr(uint8_t addr);
	void writeData(uint8_t data);
	uint8_t readData();
	void oamDma(uint8_t* p_data);
public:
	//
	void reset(); //
	void run_1cycle(); //
	//
	int scanline; //
	int cycle; //
	uint8_t scanline_spr_dx[8];
	uint8_t scanline_spr_cnt; //
	PictureBus* p_bus;
	OAM_RAM oamram; //
	bool even_frame; //
	int frame_dx = 0;
	int frame_finished = -1;
	uint8_t frame_data[256][240][3];

	PPU2();
};

#endif
