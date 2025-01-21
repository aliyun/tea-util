import { Readable } from 'stream';
import * as $tea from '@alicloud/tea-typescript';
import * as kitx from 'kitx';
import querystring from 'querystring';
import { platform, arch } from 'os';
import * as jp from 'jsonpath';
const DEFAULT_USER_AGENT = `AlibabaCloud (${platform()}; ${arch()}) Node.js/${process.version} Core/1.0.1 TeaDSL/1`;

export class ExtendsParameters extends $tea.Model {
  headers?: { [key: string]: string };
  queries?: { [key: string]: string };
  static names(): { [key: string]: string } {
    return {
      headers: 'headers',
      queries: 'queries',
    };
  }

  static types(): { [key: string]: any } {
    return {
      headers: { 'type': 'map', 'keyType': 'string', 'valueType': 'string' },
      queries: { 'type': 'map', 'keyType': 'string', 'valueType': 'string' },
    };
  }

  constructor(map?: { [key: string]: any }) {
    super(map);
  }
}

export class RuntimeOptions extends $tea.Model {
  autoretry?: boolean;
  ignoreSSL?: boolean;
  key?: string;
  cert?: string;
  ca?: string;
  maxAttempts?: number;
  backoffPolicy?: string;
  backoffPeriod?: number;
  readTimeout?: number;
  connectTimeout?: number;
  httpProxy?: string;
  httpsProxy?: string;
  noProxy?: string;
  maxIdleConns?: number;
  keepAlive?: boolean;
  extendsParameters?: ExtendsParameters;
  static names(): { [key: string]: string } {
    return {
      autoretry: 'autoretry',
      ignoreSSL: 'ignoreSSL',
      key: 'key',
      cert: 'cert',
      ca: 'ca',
      maxAttempts: 'max_attempts',
      backoffPolicy: 'backoff_policy',
      backoffPeriod: 'backoff_period',
      readTimeout: 'readTimeout',
      connectTimeout: 'connectTimeout',
      httpProxy: 'httpProxy',
      httpsProxy: 'httpsProxy',
      noProxy: 'noProxy',
      maxIdleConns: 'maxIdleConns',
      keepAlive: 'keepAlive',
      extendsParameters: 'extendsParameters',
    };
  }

  static types(): { [key: string]: any } {
    return {
      autoretry: 'boolean',
      ignoreSSL: 'boolean',
      key: 'string',
      cert: 'string',
      ca: 'string',
      maxAttempts: 'number',
      backoffPolicy: 'string',
      backoffPeriod: 'number',
      readTimeout: 'number',
      connectTimeout: 'number',
      httpProxy: 'string',
      httpsProxy: 'string',
      noProxy: 'string',
      maxIdleConns: 'number',
      keepAlive: 'boolean',
      extendsParameters: ExtendsParameters,
    };
  }

  constructor(map?: { [key: string]: any }) {
    super(map);
  }
}

function read(readable: Readable): Promise<Buffer> {
  return new Promise((resolve, reject) => {
    let onData, onError, onEnd;
    var cleanup = function () {
      // cleanup
      readable.removeListener('error', onError);
      readable.removeListener('data', onData);
      readable.removeListener('end', onEnd);
    };

    var bufs = [];
    var size = 0;

    onData = function (buf) {
      bufs.push(buf);
      size += buf.length;
    };

    onError = function (err) {
      cleanup();
      reject(err);
    };

    onEnd = function () {
      cleanup();
      resolve(Buffer.concat(bufs, size));
    };

    readable.on('error', onError);
    readable.on('data', onData);
    readable.on('end', onEnd);
  });
}

function parseToMap(input: any): { [key: string]: any } {
  return toMap(input);
}

function isObjectOrArray(t: any): boolean {
  return Array.isArray(t) || (t instanceof Object && typeof t !== 'function');
}

function toMap(input: any) {
  if (!isObjectOrArray(input)) {
    return null;
  } else if (input instanceof $tea.Model) {
    return $tea.toMap(input);
  } else if (input && input.toMap && typeof input.toMap === 'function') {
    // 解决跨版本 Model 不互认的问题
    return input.toMap();
  } else if (Array.isArray(input)) {
    const result = [];
    input.forEach((value) => {
      if (isObjectOrArray(value)) {
        result.push(toMap(value));
      } else {
        result.push(value);
      }
    });

    return result;
  } else if (input instanceof Object) {
    const result = {};
    Object.entries(input).forEach(([key, value]) => {
      if (isObjectOrArray(value)) {
        result[key] = toMap(value);
      } else {
        result[key] = value;
      }
    });

    return result;
  }
}

export default class Client {

  static toString(buff: Buffer): string {
    return buff.toString();
  }

  static parseJSON(text: string): any {
    return JSON.parse(text);
  }

  static readPath(obj: Object, path: string) {
    return jp.query(parseToMap(obj), path);
  }

  static async readAsBytes(stream: Readable): Promise<Buffer> {
    return await read(stream);
  }

  static async readAsString(stream: Readable): Promise<string> {
    let buff = await Client.readAsBytes(stream);
    return Client.toString(buff);
  }

  static async readAsJSON(stream: Readable): Promise<any> {
    return Client.parseJSON(await Client.readAsString(stream));
  }

  static getNonce(): string {
    return kitx.makeNonce();
  }

  static getDateUTCString(): string {
    const now = new Date();
    return now.toUTCString();
  }

  static defaultString(real: string, defaultValue: string): string {
    return real || defaultValue;
  }

  static defaultNumber(real: number, defaultValue: number): number {
    return real || defaultValue;
  }

  static toFormString(val: { [key: string]: any }): string {
    return querystring.stringify(val);
  }

  static toJSONString(val: any): string {
    if (typeof val === 'string') {
      return val;
    }
    return JSON.stringify(val);
  }

  static toBytes(val: string): Buffer {
    return Buffer.from(val);
  }

  static empty(val: string): boolean {
    return !val;
  }

  static equalString(val1: string, val2: string): boolean {
    return val1 === val2;
  }

  static equalNumber(val1: number, val2: number): boolean {
    return val1 === val2;
  }

  static isUnset(value: any): boolean {
    if (typeof value === 'undefined') {
      return true;
    }

    if (value === null) {
      return true;
    }

    return false;
  }

  static stringifyMapValue(m: { [key: string]: any }): { [key: string]: string } {
    if (!m) {
      return m;
    }

    const result: { [key: string]: string } = {};
    for (const [key, value] of Object.entries(m)) {
      if (typeof value === 'undefined' || value === null) {
        continue;
      }
      result[key] = String(value);
    }
    return result;
  }

  static anyifyMapValue(m: { [key: string]: string }): { [key: string]: any } {
    return m;
  }

  static assertAsBoolean(value: any): boolean {
    if (typeof value === 'boolean') {
      return value;
    }
    throw new Error(`The value is not a boolean`);
  }

  static assertAsString(value: any): string {
    if (typeof value === 'string') {
      return value;
    }
    throw new Error(`The value is not a string`);
  }

  static assertAsNumber(value: any): number {
    if (typeof value === 'number') {
      return value;
    }
    throw new Error(`The value is not a number`);
  }

  /**
   * Assert a value, if it is a integer, return it, otherwise throws
   * @return the integer value
   */
  static assertAsInteger(value: any): number {
    if (Number.isInteger(value)) {
      return value;
    }
    throw new Error(`The value is not a int number`);
  }

  static assertAsMap(value: any): { [key: string]: any } {
    if (value && typeof value === 'object' && !Array.isArray(value)) {
      return value as { [key: string]: any };
    }
    throw new Error(`The value is not a object`);
  }

  static assertAsArray(value: any): any[] {
    if (Array.isArray(value)) {
      return value;
    }
    throw new Error(`The value is not array`);
  }

  static assertAsBytes(value: any): Buffer {
    if (Buffer.isBuffer(value)) {
      return value;
    }
    throw new Error(`The value is not bytes`);
  }

  static getUserAgent(userAgent: string): string {
    if (!userAgent || !userAgent.length) {
      return DEFAULT_USER_AGENT;
    }
    return DEFAULT_USER_AGENT + " " + userAgent;
  }

  static is2xx(code: number): boolean {
    return code >= 200 && code < 300;
  }

  static is3xx(code: number): boolean {
    return code >= 300 && code < 400;
  }

  static is4xx(code: number): boolean {
    return code >= 400 && code < 500;
  }

  static is5xx(code: number): boolean {
    return code >= 500 && code < 600;
  }
  static validateModel(m: $tea.Model): void {

  }

  static toMap(inputModel: $tea.Model): { [key: string]: any } {
    return $tea.toMap(inputModel);
  }

  static async sleep(millisecond: number): Promise<void> {
    return new Promise(resolve => {
      setTimeout(() => {
        resolve();
      }, millisecond)
    })
  }

  static toArray(input: any): { [key: string]: any }[] {
    if (!(input instanceof Array)) {
      return null;
    }
    let ret = [];
    input.forEach((model) => {
      if (!model) {
        return;
      }
      ret.push($tea.toMap(model));
    })
    return ret;
  }

  /**
   * Assert a value, if it is a readable, return it, otherwise throws
   * @return the readable value
   */
  static assertAsReadable(value: any): Readable {
    if (value instanceof Readable) {
      return value;
    }
    throw new Error(`The value is not a readable`);
  }
}


