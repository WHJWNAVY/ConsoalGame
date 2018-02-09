#ifndef FONT5X7_H
#define FONT5X7_H

static const int font5X7Height = 7;
static const int font5X7Width = 5;

#if 1
static unsigned char font_5x7[] =
{
    /*00*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* */
    /*01*/ 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, /*!*/
    /*02*/ 0xA0, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, /*"*/
    /*03*/ 0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50, /*#*/
    /*04*/ 0x20, 0x78, 0xA0, 0x70, 0x28, 0xF0, 0x20, /*$*/
    /*05*/ 0xC0, 0xC8, 0x10, 0x20, 0x40, 0x98, 0x18, /*%*/
    /*06*/ 0x60, 0x90, 0xA0, 0x40, 0xA8, 0x90, 0x68, /*&*/
    /*07*/ 0xC0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, /*'*/
    /*08*/ 0x20, 0x40, 0x80, 0x80, 0x80, 0x40, 0x20, /*(*/
    /*09*/ 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, /*)*/
    /*10*/ 0x00, 0x50, 0x20, 0xF8, 0x20, 0x50, 0x00, /***/
    /*11*/ 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, /*+*/
    /*12*/ 0x00, 0x00, 0x00, 0x00, 0xC0, 0x40, 0x80, /*,*/
    /*13*/ 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, /*-*/
    /*14*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, /*.*/
    /*15*/ 0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, /*/*/
    /*16*/ 0x70, 0x88, 0x98, 0xA8, 0xC8, 0x88, 0x70, /*0*/
    /*17*/ 0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, /*1*/
    /*18*/ 0x70, 0x88, 0x08, 0x30, 0x40, 0x80, 0xF8, /*2*/
    /*19*/ 0x70, 0x88, 0x08, 0x30, 0x08, 0x88, 0x70, /*3*/
    /*20*/ 0x10, 0x30, 0x50, 0x90, 0xF8, 0x10, 0x10, /*4*/
    /*21*/ 0xF8, 0x80, 0xF0, 0x08, 0x08, 0x88, 0x70, /*5*/
    /*22*/ 0x30, 0x40, 0x80, 0xF0, 0x88, 0x88, 0x70, /*6*/
    /*23*/ 0xF8, 0x08, 0x10, 0x20, 0x40, 0x40, 0x40, /*7*/
    /*24*/ 0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, /*8*/
    /*25*/ 0x70, 0x88, 0x88, 0x78, 0x08, 0x10, 0x60, /*9*/
    /*26*/ 0x00, 0xC0, 0xC0, 0x00, 0xC0, 0xC0, 0x00, /*:*/
    /*27*/ 0x00, 0xC0, 0xC0, 0x00, 0xC0, 0x40, 0x80, /*;*/
    /*28*/ 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, /*<*/
    /*29*/ 0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00, /*=*/
    /*30*/ 0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80, /*>*/
    /*31*/ 0x70, 0x88, 0x08, 0x10, 0x20, 0x00, 0x20, /*?*/
    /*32*/ 0x70, 0x88, 0x08, 0x68, 0xA8, 0xA8, 0x70, /*@*/
    /*33*/ 0x70, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, /*A*/
    /*34*/ 0xF0, 0x88, 0x88, 0xF0, 0x88, 0x88, 0xF0, /*B*/
    /*35*/ 0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, /*C*/
    /*36*/ 0xE0, 0x90, 0x88, 0x88, 0x88, 0x90, 0xE0, /*D*/
    /*37*/ 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, /*E*/
    /*38*/ 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0x80, /*F*/
    /*39*/ 0x70, 0x88, 0x80, 0x80, 0x98, 0x88, 0x78, /*G*/
    /*40*/ 0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, /*H*/
    /*41*/ 0xE0, 0x40, 0x40, 0x40, 0x40, 0x40, 0xE0, /*I*/
    /*42*/ 0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60, /*J*/
    /*43*/ 0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88, /*K*/
    /*44*/ 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, /*L*/
    /*45*/ 0x88, 0xD8, 0xA8, 0xA8, 0x88, 0x88, 0x88, /*M*/
    /*46*/ 0x88, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, /*N*/
    /*47*/ 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, /*O*/
    /*48*/ 0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, /*P*/
    /*49*/ 0x70, 0x88, 0x88, 0x88, 0xA8, 0x90, 0x68, /*Q*/
    /*50*/ 0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88, /*R*/
    /*51*/ 0x70, 0x88, 0x80, 0x70, 0x08, 0x88, 0x70, /*S*/
    /*52*/ 0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, /*T*/
    /*53*/ 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, /*U*/
    /*54*/ 0x88, 0x88, 0x88, 0x88, 0x88, 0x50, 0x20, /*V*/
    /*55*/ 0x88, 0x88, 0x88, 0xA8, 0xA8, 0xA8, 0x50, /*W*/
    /*56*/ 0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, /*X*/
    /*57*/ 0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20, /*Y*/
    /*58*/ 0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8, /*Z*/
    /*59*/ 0xE0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xE0, /*[*/
    /*60*/ 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00, /*\*/
    /*61*/ 0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, /*]*/
    /*62*/ 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, /*^*/
    /*63*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, /*_*/
    /*64*/ 0x80, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, /*`*/
    /*65*/ 0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, /*a*/
    /*66*/ 0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0xF0, /*b*/
    /*67*/ 0x00, 0x00, 0x60, 0x90, 0x80, 0x90, 0x60, /*c*/
    /*68*/ 0x08, 0x08, 0x68, 0x98, 0x88, 0x88, 0x78, /*d*/
    /*69*/ 0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, /*e*/
    /*70*/ 0x20, 0x50, 0x40, 0xE0, 0x40, 0x40, 0x40, /*f*/
    /*71*/ 0x00, 0x78, 0x88, 0x88, 0x78, 0x08, 0x70, /*g*/
    /*72*/ 0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0x88, /*h*/
    /*73*/ 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, /*i*/
    /*74*/ 0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0xC0, /*j*/
    /*75*/ 0x80, 0x80, 0x90, 0xA0, 0xC0, 0xA0, 0x90, /*k*/
    /*76*/ 0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0xE0, /*l*/
    /*77*/ 0x00, 0x00, 0xD0, 0xA8, 0x88, 0x88, 0x88, /*m*/
    /*78*/ 0x00, 0x00, 0xB0, 0xD0, 0x90, 0x90, 0x90, /*n*/
    /*79*/ 0x00, 0x00, 0x60, 0x90, 0x90, 0x90, 0x60, /*o*/
    /*80*/ 0x00, 0xE0, 0x90, 0x90, 0xE0, 0x80, 0x80, /*p*/
    /*81*/ 0x00, 0x70, 0x90, 0x90, 0x70, 0x10, 0x10, /*q*/
    /*82*/ 0x00, 0x00, 0xA0, 0xC0, 0x80, 0x80, 0x80, /*r*/
    /*83*/ 0x00, 0x00, 0x70, 0x80, 0x60, 0x10, 0xE0, /*s*/
    /*84*/ 0x40, 0x40, 0xE0, 0x40, 0x40, 0x40, 0x40, /*t*/
    /*85*/ 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x70, /*u*/
    /*86*/ 0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20, /*v*/
    /*87*/ 0x00, 0x00, 0x88, 0x88, 0xA8, 0xA8, 0x50, /*w*/
    /*88*/ 0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, /*x*/
    /*89*/ 0x00, 0x90, 0x90, 0x90, 0x70, 0x10, 0x60, /*y*/
    /*90*/ 0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0xF8, /*z*/
    /*91*/ 0x20, 0x40, 0x40, 0x80, 0x40, 0x40, 0x20, /*{*/
    /*92*/ 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, /*|*/
    /*93*/ 0x80, 0x40, 0x40, 0x20, 0x40, 0x40, 0x80, /*}*/
    /*94*/ 0x68, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, /*~*/
    /*95*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /**/
};
#else
static unsigned char font_5x7[] =
{
    /*00*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* */
    /*01*/ 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, /*!*/
    /*02*/ 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, /*"*/
    /*03*/ 0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50, /*#*/
    /*04*/ 0x20, 0x78, 0xA0, 0x70, 0x28, 0xF0, 0x20, /*$*/
    /*05*/ 0xC0, 0xC8, 0x10, 0x20, 0x40, 0x98, 0x18, /*%*/
    /*06*/ 0x60, 0x90, 0xA0, 0x40, 0xA8, 0x90, 0x68, /*&*/
    /*07*/ 0x60, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, /*'*/
    /*08*/ 0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10, /*(*/
    /*09*/ 0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40, /*)*/
    /*10*/ 0x00, 0x50, 0x20, 0xF8, 0x20, 0x50, 0x00, /***/
    /*11*/ 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, /*+*/
    /*12*/ 0x00, 0x00, 0x00, 0x00, 0x60, 0x20, 0x40, /*,*/
    /*13*/ 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, /*-*/
    /*14*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, /*.*/
    /*15*/ 0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, /*/*/
    /*16*/ 0x70, 0x88, 0x98, 0xA8, 0xC8, 0x88, 0x70, /*0*/
    /*17*/ 0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, /*1*/
    /*18*/ 0x70, 0x88, 0x08, 0x10, 0x20, 0x40, 0xF8, /*2*/
    /*19*/ 0xF8, 0x10, 0x20, 0x10, 0x08, 0x88, 0x70, /*3*/
    /*20*/ 0x10, 0x30, 0x50, 0x90, 0xF8, 0x10, 0x10, /*4*/
    /*21*/ 0xF8, 0x80, 0xF0, 0x08, 0x08, 0x88, 0x70, /*5*/
    /*22*/ 0x30, 0x40, 0x80, 0xF0, 0x88, 0x88, 0x70, /*6*/
    /*23*/ 0xF8, 0x08, 0x10, 0x20, 0x40, 0x40, 0x40, /*7*/
    /*24*/ 0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, /*8*/
    /*25*/ 0x70, 0x88, 0x88, 0x78, 0x08, 0x10, 0x60, /*9*/
    /*26*/ 0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00, /*:*/
    /*27*/ 0x00, 0x60, 0x60, 0x00, 0x60, 0x20, 0x40, /*;*/
    /*28*/ 0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, /*<*/
    /*29*/ 0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00, /*=*/
    /*30*/ 0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80, /*>*/
    /*31*/ 0x70, 0x88, 0x08, 0x10, 0x20, 0x00, 0x20, /*?*/
    /*32*/ 0x70, 0x88, 0x08, 0x68, 0xA8, 0xA8, 0x70, /*@*/
    /*33*/ 0x70, 0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, /*A*/
    /*34*/ 0xF0, 0x88, 0x88, 0xF0, 0x88, 0x88, 0xF0, /*B*/
    /*35*/ 0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, /*C*/
    /*36*/ 0xE0, 0x90, 0x88, 0x88, 0x88, 0x90, 0xE0, /*D*/
    /*37*/ 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, /*E*/
    /*38*/ 0xF8, 0x80, 0x80, 0xE0, 0x80, 0x80, 0x80, /*F*/
    /*39*/ 0x70, 0x88, 0x80, 0x80, 0x98, 0x88, 0x70, /*G*/
    /*40*/ 0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, /*H*/
    /*41*/ 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, /*I*/
    /*42*/ 0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60, /*J*/
    /*43*/ 0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88, /*K*/
    /*44*/ 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, /*L*/
    /*45*/ 0x88, 0xD8, 0xA8, 0x88, 0x88, 0x88, 0x88, /*M*/
    /*46*/ 0x88, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, /*N*/
    /*47*/ 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, /*O*/
    /*48*/ 0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, /*P*/
    /*49*/ 0x70, 0x88, 0x88, 0x88, 0xA8, 0x90, 0x68, /*Q*/
    /*50*/ 0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88, /*R*/
    /*51*/ 0x78, 0x80, 0x80, 0x70, 0x08, 0x08, 0xF0, /*S*/
    /*52*/ 0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, /*T*/
    /*53*/ 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, /*U*/
    /*54*/ 0x88, 0x88, 0x88, 0x88, 0x88, 0x50, 0x20, /*V*/
    /*55*/ 0x88, 0x88, 0x88, 0xA8, 0xA8, 0xD8, 0x88, /*W*/
    /*56*/ 0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, /*X*/
    /*57*/ 0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20, /*Y*/
    /*58*/ 0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8, /*Z*/
    /*59*/ 0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38, /*[*/
    /*60*/ 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00, /*\*/
    /*61*/ 0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0, /*]*/
    /*62*/ 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, /*^*/
    /*63*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, /*_*/
    /*64*/ 0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, /*`*/
    /*65*/ 0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, /*a*/
    /*66*/ 0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0xF0, /*b*/
    /*67*/ 0x00, 0x00, 0x70, 0x80, 0x80, 0x88, 0x70, /*c*/
    /*68*/ 0x08, 0x08, 0x68, 0x98, 0x88, 0x88, 0x78, /*d*/
    /*69*/ 0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, /*e*/
    /*70*/ 0x30, 0x48, 0x40, 0xE0, 0x40, 0x40, 0x40, /*f*/
    /*71*/ 0x00, 0x00, 0x78, 0x88, 0x78, 0x08, 0x70, /*g*/
    /*72*/ 0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0x88, /*h*/
    /*73*/ 0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, /*i*/
    /*74*/ 0x10, 0x00, 0x30, 0x10, 0x10, 0x90, 0x60, /*j*/
    /*75*/ 0x40, 0x40, 0x48, 0x50, 0x60, 0x50, 0x48, /*k*/
    /*76*/ 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, /*l*/
    /*77*/ 0x00, 0x00, 0xD0, 0xA8, 0xA8, 0x88, 0x88, /*m*/
    /*78*/ 0x00, 0x00, 0xB0, 0xC8, 0x88, 0x88, 0x88, /*n*/
    /*79*/ 0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, /*o*/
    /*80*/ 0x00, 0x00, 0xF0, 0x88, 0xF0, 0x80, 0x80, /*p*/
    /*81*/ 0x00, 0x00, 0x68, 0x98, 0x78, 0x08, 0x08, /*q*/
    /*82*/ 0x00, 0x00, 0xB0, 0xC8, 0x80, 0x80, 0x80, /*r*/
    /*83*/ 0x00, 0x00, 0x70, 0x80, 0x70, 0x08, 0xF0, /*s*/
    /*84*/ 0x40, 0x40, 0xE0, 0x40, 0x40, 0x48, 0x30, /*t*/
    /*85*/ 0x00, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68, /*u*/
    /*86*/ 0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20, /*v*/
    /*87*/ 0x00, 0x00, 0x88, 0x88, 0xA8, 0xA8, 0x50, /*w*/
    /*88*/ 0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, /*x*/
    /*89*/ 0x00, 0x00, 0x88, 0x88, 0x78, 0x08, 0x70, /*y*/
    /*90*/ 0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0xF8, /*z*/
    /*91*/ 0x10, 0x20, 0x20, 0x40, 0x20, 0x20, 0x10, /*{*/
    /*92*/ 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, /*|*/
    /*93*/ 0x40, 0x20, 0x20, 0x10, 0x20, 0x20, 0x40, /*}*/
    /*94*/ 0x00, 0x20, 0x10, 0xF8, 0x10, 0x20, 0x00, /*~*/
    /*95*/ 0x00, 0x20, 0x40, 0xF8, 0x40, 0x20, 0x00, /**/
};
#endif

#endif