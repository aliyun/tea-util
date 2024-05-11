import Foundation
import Tea

public class ExtendsParameters : Tea.TeaModel {
    public var headers: [String: String]?

    public override init() {
        super.init()
    }

    public init(_ dict: [String: Any]) {
        super.init()
        self.fromMap(dict)
    }

    public override func validate() throws -> Void {
    }

    public override func toMap() -> [String : Any] {
        var map = super.toMap()
        if self.headers != nil {
            map["headers"] = self.headers!
        }
        return map
    }

    public override func fromMap(_ dict: [String: Any]) -> Void {
        if dict.keys.contains("headers") {
            self.headers = dict["headers"] as! [String: String]
        }
    }
}

public class RuntimeOptions : Tea.TeaModel {
    public var autoretry: Bool?

    public var ignoreSSL: Bool?

    public var key: String?

    public var cert: String?

    public var ca: String?

    public var maxAttempts: Int?

    public var backoffPolicy: String?

    public var backoffPeriod: Int?

    public var readTimeout: Int?

    public var connectTimeout: Int?

    public var httpProxy: String?

    public var httpsProxy: String?

    public var noProxy: String?

    public var maxIdleConns: Int?

    public var localAddr: String?

    public var socks5Proxy: String?

    public var socks5NetWork: String?

    public var keepAlive: Bool?

    public var extendsParameters: ExtendsParameters?

    public override init() {
        super.init()
    }

    public init(_ dict: [String: Any]) {
        super.init()
        self.fromMap(dict)
    }

    public override func validate() throws -> Void {
        try self.extendsParameters?.validate()
    }

    public override func toMap() -> [String : Any] {
        var map = super.toMap()
        if self.autoretry != nil {
            map["autoretry"] = self.autoretry!
        }
        if self.ignoreSSL != nil {
            map["ignoreSSL"] = self.ignoreSSL!
        }
        if self.key != nil {
            map["key"] = self.key!
        }
        if self.cert != nil {
            map["cert"] = self.cert!
        }
        if self.ca != nil {
            map["ca"] = self.ca!
        }
        if self.maxAttempts != nil {
            map["max_attempts"] = self.maxAttempts!
        }
        if self.backoffPolicy != nil {
            map["backoff_policy"] = self.backoffPolicy!
        }
        if self.backoffPeriod != nil {
            map["backoff_period"] = self.backoffPeriod!
        }
        if self.readTimeout != nil {
            map["readTimeout"] = self.readTimeout!
        }
        if self.connectTimeout != nil {
            map["connectTimeout"] = self.connectTimeout!
        }
        if self.httpProxy != nil {
            map["httpProxy"] = self.httpProxy!
        }
        if self.httpsProxy != nil {
            map["httpsProxy"] = self.httpsProxy!
        }
        if self.noProxy != nil {
            map["noProxy"] = self.noProxy!
        }
        if self.maxIdleConns != nil {
            map["maxIdleConns"] = self.maxIdleConns!
        }
        if self.localAddr != nil {
            map["localAddr"] = self.localAddr!
        }
        if self.socks5Proxy != nil {
            map["socks5Proxy"] = self.socks5Proxy!
        }
        if self.socks5NetWork != nil {
            map["socks5NetWork"] = self.socks5NetWork!
        }
        if self.keepAlive != nil {
            map["keepAlive"] = self.keepAlive!
        }
        if self.extendsParameters != nil {
            map["extendsParameters"] = self.extendsParameters?.toMap()
        }
        return map
    }

    public override func fromMap(_ dict: [String: Any]) -> Void {
        if dict.keys.contains("autoretry") {
            self.autoretry = dict["autoretry"] as! Bool
        }
        if dict.keys.contains("ignoreSSL") {
            self.ignoreSSL = dict["ignoreSSL"] as! Bool
        }
        if dict.keys.contains("key") {
            self.key = dict["key"] as! String
        }
        if dict.keys.contains("cert") {
            self.cert = dict["cert"] as! String
        }
        if dict.keys.contains("ca") {
            self.ca = dict["ca"] as! String
        }
        if dict.keys.contains("max_attempts") {
            self.maxAttempts = dict["max_attempts"] as! Int
        }
        if dict.keys.contains("backoff_policy") {
            self.backoffPolicy = dict["backoff_policy"] as! String
        }
        if dict.keys.contains("backoff_period") {
            self.backoffPeriod = dict["backoff_period"] as! Int
        }
        if dict.keys.contains("readTimeout") {
            self.readTimeout = dict["readTimeout"] as! Int
        }
        if dict.keys.contains("connectTimeout") {
            self.connectTimeout = dict["connectTimeout"] as! Int
        }
        if dict.keys.contains("httpProxy") {
            self.httpProxy = dict["httpProxy"] as! String
        }
        if dict.keys.contains("httpsProxy") {
            self.httpsProxy = dict["httpsProxy"] as! String
        }
        if dict.keys.contains("noProxy") {
            self.noProxy = dict["noProxy"] as! String
        }
        if dict.keys.contains("maxIdleConns") {
            self.maxIdleConns = dict["maxIdleConns"] as! Int
        }
        if dict.keys.contains("localAddr") {
            self.localAddr = dict["localAddr"] as! String
        }
        if dict.keys.contains("socks5Proxy") {
            self.socks5Proxy = dict["socks5Proxy"] as! String
        }
        if dict.keys.contains("socks5NetWork") {
            self.socks5NetWork = dict["socks5NetWork"] as! String
        }
        if dict.keys.contains("keepAlive") {
            self.keepAlive = dict["keepAlive"] as! Bool
        }
        if dict.keys.contains("extendsParameters") {
            var model = ExtendsParameters()
            model.fromMap(dict["extendsParameters"] as! [String: Any])
            self.extendsParameters = model
        }
    }
}
