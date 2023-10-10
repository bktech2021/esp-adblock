#include <ESP8266WiFi.h>
#include "DNSServer.h"
#include <ESP8266WebServer.h>
#define SSID "YOUR_SSID"
#define PASS "YOUR_PASS"

const byte DNS_PORT = 53;
IPAddress adIP(0, 0, 0, 0);
DNSServer dnsServer;
String table[] = { "gtm.mouseflow.com", "a.nel.cloudflare.com", "www.luckyorange.com", "cdn.mouseflow.com", "www.adtech.yahooinc.com", "o2.mouseflow.com", "adtago.s3.amazonaws.com", "analyticsengine.s3.amazonaws.com", "analytics.s3.amazonaws.com", "advice-ads.s3.amazonaws.com", "advertising-api-eu.amazon.com", "pagead2.googlesyndication.com", "adservice.google.com", "pagead2.googleadservices.com", "afs.googlesyndication.com", "stats.g.doubleclick.net", "ad.doubleclick.net", "static.doubleclick.net", "m.doubleclick.net", "mediavisor.doubleclick.net", "ads30.adcolony.com", "adc3-launch.adcolony.com", "events3alt.adcolony.com", "wd.adcolony.com", "static.media.net", "media.net", "adservetx.media.net", "app-measurement.com", "analytics.google.com", "click.googleanalytics.com", "google-analytics.com", "ssl.google-analytics.com", "adm.hotjar.com", "identify.hotjar.com", "insights.hotjar.com", "script.hotjar.com", "surveys.hotjar.com", "careers.hotjar.com", "events.hotjar.io", "mouseflow.com", "api.mouseflow.com", "tools.mouseflow.com", "cdn-test.mouseflow.com", "freshmarketer.com", "claritybt.freshmarketer.com", "fwtracks.freshmarketer.com", "luckyorange.com", "api.luckyorange.com", "realtime.luckyorange.com", "cdn.luckyorange.com", "w1.luckyorange.com", "upload.luckyorange.net", "cs.luckyorange.net", "settings.luckyorange.net", "stats.wp.com", "notify.bugsnag.com", "sessions.bugsnag.com", "api.bugsnag.com", "app.bugsnag.com", "browser.sentry-cdn.com", "app.getsentry.com", "pixel.facebook.com", "an.facebook.com", "static.ads-twitter.com", "ads-api.twitter.com", "ads.linkedin.com", "analytics.pointdrive.linkedin.com", "ads.pinterest.com", "log.pinterest.com", "analytics.pinterest.com", "trk.pinterest.com", "widgets.pinterest.com", "events.reddit.com", "events.redditmedia.com", "ads.youtube.com", "ads-api.tiktok.com", "analytics.tiktok.com", "ads-sg.tiktok.com", "analytics-sg.tiktok.com", "business-api.tiktok.com", "ads.tiktok.com", "log.byteoversea.com", "ads.yahoo.com", "analytics.yahoo.com", "geo.yahoo.com", "udc.yahoo.com", "udcm.yahoo.com", "advertising.yahoo.com", "analytics.query.yahoo.com", "partnerads.ysm.yahoo.com", "log.fc.yahoo.com", "gemini.yahoo.com", "adtech.yahooinc.com", "extmaps-api.yandex.net", "appmetrica.yandex.ru", "adfstat.yandex.ru", "metrika.yandex.ru", "advertising.yandex.ru", "offerwall.yandex.net", "adfox.yandex.ru", "auction.unityads.unity3d.com", "webview.unityads.unity3d.com", "config.unityads.unity3d.com", "adserver.unityads.unity3d.com", "iot-eu-logser.realme.com", "iot-logser.realme.com", "bdapi-ads.realmemobile.com", "bdapi-in-ads.realmemobile.com", "api.ad.xiaomi.com", "data.mistat.xiaomi.com", "data.mistat.india.xiaomi.com", "data.mistat.rus.xiaomi.com", "sdkconfig.ad.xiaomi.com", "sdkconfig.ad.intl.xiaomi.com", "globalapi.ad.xiaomi.com", "tracking.rus.miui.com", "adsfs.oppomobile.com", "adx.ads.oppomobile.com", "ck.ads.oppomobile.com", "data.ads.oppomobile.com", "metrics.data.hicloud.com", "metrics2.data.hicloud.com", "grs.hicloud.com", "logservice.hicloud.com", "logservice1.hicloud.com", "logbak.hicloud.com", "click.oneplus.cn", "open.oneplus.net", "samsungads.com", "smetrics.samsung.com", "nmetrics.samsung.com", "samsung-com.112.2o7.net", "analytics-api.samsunghealthcn.com", "advertising.apple.com", "tr.iadsdk.apple.com", "iadsdk.apple.com", "metrics.icloud.com", "metrics.apple.com", "metrics.mzstatic.com", "api-adservices.apple.com", "books-analytics-events.apple.com", "weather-analytics-events.apple.com", "notes-analytics-events.apple.com" };
bool ad = false;
IPAddress ip;

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(2, OUTPUT);
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    digitalWrite(2, !digitalRead(2));
  }

  Serial.println("");
  Serial.print("WiFi connected | IP address: ");
  Serial.println(WiFi.localIP());
  // modify TTL associated  with the domain name (in seconds)
  // default is 60 seconds
  dnsServer.setTTL(300);
  // set which return code will be used for all other domains (e.g. sending
  // ServerFailure instead of NonExistentDomain will reduce number of queries
  // sent by clients)
  // default is DNSReplyCode::NonExistentDomain
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);

  // start DNS server for a specific domain name
  dnsServer.start(DNS_PORT, "*", WiFi.localIP());
}

void loop() {
  if (!dnsServer.processNextRequest()) {
    String dom = dnsServer.getQueryDomainName();
    for (int i = 0; i <= 142; i++) {
      if (dom == table[i]) {
        dnsServer.replyWithIP(IPAddress(0, 0, 0, 0));
        return;
      }
    }
    ip;
    WiFi.hostByName(dom.c_str(), ip);
    dnsServer.replyWithIP(ip);
  }
}
