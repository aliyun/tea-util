import Foundation
import Tea

public class ExtendsParameters : Tea.TeaModel {
    public var headers: [String: String]?

    public var queries: [String: String]?

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
        if self.queries != nil {
            map["queries"] = self.queries!
        }
        return map
    }

    public override func fromMap(_ dict: [String: Any?]?) -> Void {
        guard let dict else { return }
        if let value = dict["headers"] as? [String: String] {
            self.headers = value
        }
        if let value = dict["queries"] as? [String: String] {
            self.queries = value
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

    public override func fromMap(_ dict: [String: Any?]?) -> Void {
        guard let dict else { return }
        if let value = dict["autoretry"] as? Bool {
            self.autoretry = value
        }
        if let value = dict["ignoreSSL"] as? Bool {
            self.ignoreSSL = value
        }
        if let value = dict["key"] as? String {
            self.key = value
        }
        if let value = dict["cert"] as? String {
            self.cert = value
        }
        if let value = dict["ca"] as? String {
            self.ca = value
        }
        if let value = dict["max_attempts"] as? Int {
            self.maxAttempts = value
        }
        if let value = dict["backoff_policy"] as? String {
            self.backoffPolicy = value
        }
        if let value = dict["backoff_period"] as? Int {
            self.backoffPeriod = value
        }
        if let value = dict["readTimeout"] as? Int {
            self.readTimeout = value
        }
        if let value = dict["connectTimeout"] as? Int {
            self.connectTimeout = value
        }
        if let value = dict["httpProxy"] as? String {
            self.httpProxy = value
        }
        if let value = dict["httpsProxy"] as? String {
            self.httpsProxy = value
        }
        if let value = dict["noProxy"] as? String {
            self.noProxy = value
        }
        if let value = dict["maxIdleConns"] as? Int {
            self.maxIdleConns = value
        }
        if let value = dict["localAddr"] as? String {
            self.localAddr = value
        }
        if let value = dict["socks5Proxy"] as? String {
            self.socks5Proxy = value
        }
        if let value = dict["socks5NetWork"] as? String {
            self.socks5NetWork = value
        }
        if let value = dict["keepAlive"] as? Bool {
            self.keepAlive = value
        }
        if let value = dict["extendsParameters"] as? [String: Any?] {
            var model = ExtendsParameters()
            model.fromMap(value)
            self.extendsParameters = model
        }
    }
}
