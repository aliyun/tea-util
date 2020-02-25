// import { Readable } from 'stream';
// import * as $tea from '@alicloud/tea-typescript';
// import * as kitx from 'kitx';
// import querystring from 'querystring';
// import { platform, arch } from 'os';
// const DEFAULT_USER_AGENT = `AlibabaCloud (${platform()}; ${arch()}) Node.js/${process.version} Core/1.0.1 TeaDSL/1`;

#include <iostream>
#include <unordered_map>
#include <sstream>
#include "Util.h"

using namespace std;
using namespace Tea;
using namespace Util;

string Client::toString(char * buff) {
    return string(buff);
}

//   static parseJSON(text: string): any {
//     return JSON.parse(text);
//   }

//   static async readAsBytes(stream: Readable): Promise<Buffer> {
//     return await read(stream);
//   }

//   static async readAsString(stream: Readable): Promise<string> {
//     let buff = await Client.readAsBytes(stream);
//     return Client.toString(buff);
//   }

//   static async readAsJSON(stream: Readable): Promise<any> {
//     return Client.parseJSON(await Client.readAsString(stream));
//   }

//   static getNonce(): string {
//     return kitx.makeNonce();
//   }

string Client::getDateUTCString() {
    std::time_t t = std::time(nullptr);
    std::stringstream date;
    #if defined(__GNUG__) && __GNUC__ < 5
    char tmbuff[26];
    strftime(tmbuff, 26, "%a, %d %b %Y %T", std::gmtime(&t));
    date << tmbuff << " GMT";
    #else
    date << std::put_time(std::gmtime(&t), "%a, %d %b %Y %T GMT");
    #endif
    return date.str();
}

//   static defaultString(real: string, defaultValue: string): string {
//     return real || defaultValue;
//   }

//   static defaultNumber(real: number, defaultValue: number): number {
//     return real || defaultValue;
//   }

//   static toFormString(val: {[key: string]: any}): string {
//     return querystring.stringify(val);
//   }

//   static toJSONString(val: any): string {
//     return JSON.stringify(val);
//   }

//   static toBytes(val: string): Buffer {
//     return Buffer.from(val);
//   }

//   static empty(val: string): boolean {
//     return !val;
//   }

//   static equalString(val1: string, val2: string): boolean {
//     return val1 === val2;
//   }

//   static equalNumber(val1: number, val2: number): boolean {
//     return val1 === val2;
//   }

//   static isUnset(value: any): boolean {
//     if (typeof value === 'undefined') {
//       return true;
//     }

//     if (value === null) {
//       return true;
//     }

//     return false;
//   }

//   static stringifyMapValue(m: {[key: string]: any} ): {[key: string]: string} {
//     if (!m) {
//       return m;
//     }

//     const result: {[key: string]: string} = {};
//     for (const [key, value] of Object.entries(m)) {
//       result[key] = String(value);
//     }
//     return result;
//   }

//   static assertAsBoolean(value: any): boolean {
//     if (typeof value === 'boolean') {
//       return value;
//     }
//     throw new Error(`The value is not a boolean`);
//   }

//   static assertAsString(value: any): string {
//     if (typeof value === 'string') {
//       return value;
//     }
//     throw new Error(`The value is not a string`);
//   }

//   static assertAsNumber(value: any): number {
//     if (typeof value === 'number') {
//       return value;
//     }
//     throw new Error(`The value is not a number`);
//   }

//   static assertAsMap(value: any): {[key: string]: any} {
//     if (value && typeof value === 'object' && !Array.isArray(value)) {
//       return value as {[key: string]: any};
//     }
//     throw new Error(`The value is not a object`);
//   }

//   static getUserAgent(userAgent: string): string {
//     if(!userAgent || !userAgent.length){
//       return DEFAULT_USER_AGENT;
//     }
//     return DEFAULT_USER_AGENT + " " + userAgent;
//   }
