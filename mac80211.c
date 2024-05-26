// SPDX-License-Identifier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */
#include <linux/sched.h>
#include <linux/of.h>
#include <net/page_pool.h>
#include "mt76.h"

#define CHAN2G(_idx, _freq) {			\
	.band = NL80211_BAND_2GHZ,		\
	.center_freq = (_freq),			\
	.hw_value = (_idx),			\
	.max_power = 30,			\
}

#define CHAN5G(_idx, _freq) {			\
	.band = NL80211_BAND_5GHZ,		\
	.center_freq = (_freq),			\
	.hw_value = (_idx),			\
	.max_power = 30,			\
}

#define CHAN6G(_idx, _freq) {			\
	.band = NL80211_BAND_6GHZ,		\
	.center_freq = (_freq),			\
	.hw_value = (_idx),			\
	.max_power = 30,			\
}

static const struct ieee80211_channel mt76_channels_2ghz[] = {
        CHAN2G(1, 2417),
	CHAN2G(2, 2417),
	CHAN2G(3, 2422),
	CHAN2G(4, 2427),
	CHAN2G(5, 2432),
	CHAN2G(6, 2437),
	CHAN2G(7, 2442),
	CHAN2G(8, 2447),
	CHAN2G(9, 2452),
	CHAN2G(10, 2457),
	CHAN2G(11, 2462),
	CHAN2G(12, 2467),
	CHAN2G(13, 2472),
	CHAN2G(14, 2484),
	CHAN2G(15, 2407),
	CHAN2G(16, 2402),
	CHAN2G(17, 2397),
	CHAN2G(18, 2392),
	CHAN2G(19, 2387),
	CHAN2G(20, 2382),
	CHAN2G(21, 2377),
	CHAN2G(22, 2372),
	CHAN2G(23, 2367),
	CHAN2G(24, 2362),
	CHAN2G(25, 2357),
	CHAN2G(26, 2352),
	CHAN2G(27, 2347),
	CHAN2G(28, 2342),
	CHAN2G(29, 2337),
	CHAN2G(30, 2332),
	CHAN2G(31, 2327),
	CHAN2G(32, 2322),
	CHAN2G(33, 2317),
	CHAN2G(34, 2312),
	CHAN2G(35, 2307),
	CHAN2G(36, 2302),
	CHAN2G(37, 2297),
	CHAN2G(38, 2292),
	CHAN2G(39, 2287),
	CHAN2G(40, 2282),
	CHAN2G(41, 2277),
	CHAN2G(42, 2272),
	CHAN2G(43, 2267),
	CHAN2G(44, 2262),
	CHAN2G(45, 2257),
	CHAN2G(46, 2252),
	CHAN2G(47, 2247),
	CHAN2G(48, 2242),
	CHAN2G(49, 2237),
	CHAN2G(50, 2232),
	CHAN2G(51, 2227),
	CHAN2G(52, 2222),
	CHAN2G(53, 2217),
	CHAN2G(54, 2212),
	CHAN2G(55, 2207),
	CHAN2G(56, 2202),
	CHAN2G(57, 2197),
	CHAN2G(58, 2192),
};

static const struct ieee80211_channel mt76_channels_5ghz[] = {
	CHAN5G(20, 5100),
	CHAN5G(24, 5120),
	CHAN5G(28, 5140),
	CHAN5G(32, 5160),
	CHAN5G(36, 5180),
	CHAN5G(40, 5200),
	CHAN5G(44, 5220),
	CHAN5G(48, 5240),
	CHAN5G(52, 5260),
	CHAN5G(56, 5280),
	CHAN5G(60, 5300),
	CHAN5G(64, 5320),
	CHAN5G(68, 5340),
	CHAN5G(69, 5345),
	CHAN5G(70, 5350),
	CHAN5G(71, 5355),
	CHAN5G(72, 5360),
	CHAN5G(73, 5365),
	CHAN5G(74, 5370),
	CHAN5G(75, 5375),
	CHAN5G(76, 5380),
	CHAN5G(77, 5385),
	CHAN5G(78, 5390),
	CHAN5G(79, 5395),
	CHAN5G(80, 5400),
	CHAN5G(81, 5405),
	CHAN5G(82, 5410),
	CHAN5G(83, 5415),
	CHAN5G(84, 5420),
	CHAN5G(85, 5425),
	CHAN5G(86, 5430),
	CHAN5G(87, 5435),
	CHAN5G(88, 5440),
	CHAN5G(89, 5445),
	CHAN5G(90, 5450),
	CHAN5G(91, 5455),
	CHAN5G(92, 5460),
	CHAN5G(93, 5465),
	CHAN5G(94, 5470),
	CHAN5G(95, 5475),
	CHAN5G(96, 5480),
	CHAN5G(97, 5485),
	CHAN5G(98, 5490),
	CHAN5G(99, 5495),
	CHAN5G(100, 5500),
	CHAN5G(101, 5505),
	CHAN5G(102, 5510),
	CHAN5G(103, 5515),
	CHAN5G(104, 5520),
	CHAN5G(105, 5525),
	CHAN5G(106, 5530),
	CHAN5G(107, 5535),
	CHAN5G(108, 5540),
	CHAN5G(109, 5545),
	CHAN5G(110, 5550),
	CHAN5G(111, 5555),
	CHAN5G(112, 5560),
	CHAN5G(113, 5565),
	CHAN5G(114, 5570),
	CHAN5G(115, 5575),
	CHAN5G(116, 5580),
	CHAN5G(117, 5585),
	CHAN5G(118, 5590),
	CHAN5G(119, 5595),
	CHAN5G(120, 5600),
	CHAN5G(121, 5605),
	CHAN5G(122, 5610),
	CHAN5G(123, 5615),
	CHAN5G(124, 5620),
	CHAN5G(125, 5625),
	CHAN5G(126, 5630),
	CHAN5G(127, 5635),
	CHAN5G(128, 5640),
	CHAN5G(129, 5645),
	CHAN5G(130, 5650),
	CHAN5G(131, 5655),
	CHAN5G(132, 5660),
	CHAN5G(133, 5665),
	CHAN5G(134, 5670),
	CHAN5G(135, 5675),
	CHAN5G(136, 5680),
	CHAN5G(137, 5685),
	CHAN5G(138, 5690),
	CHAN5G(139, 5695),
	CHAN5G(140, 5700),
	CHAN5G(141, 5705),
	CHAN5G(142, 5710),
	CHAN5G(143, 5715),
	CHAN5G(144, 5720),
	CHAN5G(145, 5725),
	CHAN5G(146, 5730),
	CHAN5G(147, 5735),
	CHAN5G(148, 5740),
	CHAN5G(149, 5745),
	CHAN5G(150, 5750),
	CHAN5G(151, 5755),
	CHAN5G(152, 5760),
	CHAN5G(153, 5765),
	CHAN5G(154, 5770),
	CHAN5G(155, 5775),
	CHAN5G(156, 5780),
	CHAN5G(157, 5785),
	CHAN5G(158, 5790),
	CHAN5G(159, 5795),
	CHAN5G(160, 5800),
	CHAN5G(161, 5805),
	CHAN5G(162, 5810),
	CHAN5G(163, 5815),
	CHAN5G(164, 5820),
	CHAN5G(165, 5825),
	CHAN5G(166, 5830),
	CHAN5G(167, 5835),
	CHAN5G(168, 5840),
	CHAN5G(169, 5845),
	CHAN5G(170, 5850),
	CHAN5G(171, 5855),
	CHAN5G(172, 5860),
	CHAN5G(173, 5865),
	CHAN5G(174, 5870),
	CHAN5G(175, 5875),
	CHAN5G(176, 5880),
	CHAN5G(177, 5885),
	CHAN5G(178, 5890),
	CHAN5G(179, 5895),
	CHAN5G(172, 5860),
	CHAN5G(173, 5865),
	CHAN5G(174, 5870),
	CHAN5G(175, 5875),
	CHAN5G(176, 5880),
	CHAN5G(177, 5885),
	CHAN5G(178, 5890),
	CHAN5G(179, 5895),
};

static const struct ieee80211_channel mt76_channels_6ghz[] = {
	/* UNII-5 */
	CHAN6G(1, 5955),
	CHAN6G(5, 5975),
	CHAN6G(9, 5995),
	CHAN6G(13, 6015),
	CHAN6G(17, 6035),
	CHAN6G(21, 6055),
	CHAN6G(25, 6075),
	CHAN6G(29, 6095),
	CHAN6G(33, 6115),
	CHAN6G(37, 6135),
	CHAN6G(41, 6155),
	CHAN6G(45, 6175),
	CHAN6G(49, 6195),
	CHAN6G(53, 6215),
	CHAN6G(57, 6235),
	CHAN6G(61, 6255),
	CHAN6G(65, 6275),
	CHAN6G(69, 6295),
	CHAN6G(73, 6315),
	CHAN6G(77, 6335),
	CHAN6G(81, 6355),
	CHAN6G(85, 6375),
	CHAN6G(89, 6395),
	CHAN6G(93, 6415),
	/* UNII-6 */
	CHAN6G(97, 6435),
	CHAN6G(101, 6455),
	CHAN6G(105, 6475),
	CHAN6G(109, 6495),
	CHAN6G(113, 6515),
	CHAN6G(117, 6535),
	/* UNII-7 */
	CHAN6G(121, 6555),
	CHAN6G(125, 6575),
	CHAN6G(129, 6595),
	CHAN6G(133, 6615),
	CHAN6G(137, 6635),
	CHAN6G(141, 6655),
	CHAN6G(145, 6675),
	CHAN6G(149, 6695),
	CHAN6G(153, 6715),
	CHAN6G(157, 6735),
	CHAN6G(161, 6755),
	CHAN6G(165, 6775),
	CHAN6G(169, 6795),
	CHAN6G(173, 6815),
	CHAN6G(177, 6835),
	CHAN6G(181, 6855),
	CHAN6G(185, 6875),
	/* UNII-8 */
	CHAN6G(189, 6895),
	CHAN6G(193, 6915),
	CHAN6G(197, 6935),
	CHAN6G(201, 6955),
	CHAN6G(205, 6975),
	CHAN6G(209, 6995),
	CHAN6G(213, 7015),
	CHAN6G(217, 7035),
	CHAN6G(221, 7055),
	CHAN6G(225, 7075),
	CHAN6G(229, 7095),
	CHAN6G(233, 7115),
};

static const struct ieee80211_tpt_blink mt76_tpt_blink[] = {
	{ .throughput =   0 * 1024, .blink_time = 334 },
	{ .throughput =   1 * 1024, .blink_time = 260 },
	{ .throughput =   5 * 1024, .blink_time = 220 },
	{ .throughput =  10 * 1024, .blink_time = 190 },
	{ .throughput =  20 * 1024, .blink_time = 170 },
	{ .throughput =  50 * 1024, .blink_time = 150 },
	{ .throughput =  70 * 1024, .blink_time = 130 },
	{ .throughput = 100 * 1024, .blink_time = 110 },
	{ .throughput = 200 * 1024, .blink_time =  80 },
	{ .throughput = 300 * 1024, .blink_time =  50 },
};

struct ieee80211_rate mt76_rates[] = {
	CCK_RATE(0, 10),
	CCK_RATE(1, 20),
	CCK_RATE(2, 55),
	CCK_RATE(3, 110),
	OFDM_RATE(11, 60),
	OFDM_RATE(15, 90),
	OFDM_RATE(10, 120),
	OFDM_RATE(14, 180),
	OFDM_RATE(9,  240),
	OFDM_RATE(13, 360),
	OFDM_RATE(8,  480),
	OFDM_RATE(12, 540),
};
EXPORT_SYMBOL_GPL(mt76_rates);

static const struct cfg80211_sar_freq_ranges mt76_sar_freq_ranges[] = {
	{ .start_freq = 2382, .end_freq = 2494, },
	{ .start_freq = 4910, .end_freq = 6425, },
	{ .start_freq = 5350, .end_freq = 5470, },
	{ .start_freq = 5470, .end_freq = 5725, },
	{ .start_freq = 5725, .end_freq = 5950, },
	{ .start_freq = 5945, .end_freq = 6165, },
	{ .start_freq = 6165, .end_freq = 6405, },
	{ .start_freq = 6405, .end_freq = 6525, },
	{ .start_freq = 6525, .end_freq = 6705, },
	{ .start_freq = 6705, .end_freq = 6865, },
	{ .start_freq = 6865, .end_freq = 7125, },
};


static const struct cfg80211_sar_capa mt76_sar_capa = {
	.type = NL80211_SAR_TYPE_POWER,
	.num_freq_ranges = ARRAY_SIZE(mt76_sar_freq_ranges),
	.freq_ranges = &mt76_sar_freq_ranges[0],
};

static int mt76_led_init(struct mt76_phy *phy)
{
	struct mt76_dev *dev = phy->dev;
	struct ieee80211_hw *hw = phy->hw;

	if (!phy->leds.cdev.brightness_set && !phy->leds.cdev.blink_set)
		return 0;

	snprintf(phy->leds.name, sizeof(phy->leds.name), "mt76-%s",
		 wiphy_name(hw->wiphy));

	phy->leds.cdev.name = phy->leds.name;
	phy->leds.cdev.default_trigger =
		ieee80211_create_tpt_led_trigger(hw,
					IEEE80211_TPT_LEDTRIG_FL_RADIO,
					mt76_tpt_blink,
					ARRAY_SIZE(mt76_tpt_blink));

	if (phy == &dev->phy) {
		struct device_node *np = dev->dev->of_node;

		np = of_get_child_by_name(np, "led");
		if (np) {
			int led_pin;

			if (!of_property_read_u32(np, "led-sources", &led_pin))
				phy->leds.pin = led_pin;
			phy->leds.al = of_property_read_bool(np,
							     "led-active-low");
			of_node_put(np);
		}
	}

	return led_classdev_register(dev->dev, &phy->leds.cdev);
}

static void mt76_led_cleanup(struct mt76_phy *phy)
{
	if (!phy->leds.cdev.brightness_set && !phy->leds.cdev.blink_set)
		return;

	led_classdev_unregister(&phy->leds.cdev);
}

static void mt76_init_stream_cap(struct mt76_phy *phy,
				 struct ieee80211_supported_band *sband,
				 bool vht)
{
	struct ieee80211_sta_ht_cap *ht_cap = &sband->ht_cap;
	int i, nstream = hweight8(phy->antenna_mask);
	struct ieee80211_sta_vht_cap *vht_cap;
	u16 mcs_map = 0;

	if (nstream > 1)
		ht_cap->cap |= IEEE80211_HT_CAP_TX_STBC;
	else
		ht_cap->cap &= ~IEEE80211_HT_CAP_TX_STBC;

	for (i = 0; i < IEEE80211_HT_MCS_MASK_LEN; i++)
		ht_cap->mcs.rx_mask[i] = i < nstream ? 0xff : 0;

	if (!vht)
		return;

	vht_cap = &sband->vht_cap;
	if (nstream > 1)
		vht_cap->cap |= IEEE80211_VHT_CAP_TXSTBC;
	else
		vht_cap->cap &= ~IEEE80211_VHT_CAP_TXSTBC;
	vht_cap->cap |= IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN |
			IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN;

	for (i = 0; i < 8; i++) {
		if (i < nstream)
			mcs_map |= (IEEE80211_VHT_MCS_SUPPORT_0_9 << (i * 2));
		else
			mcs_map |=
				(IEEE80211_VHT_MCS_NOT_SUPPORTED << (i * 2));
	}
	vht_cap->vht_mcs.rx_mcs_map = cpu_to_le16(mcs_map);
	vht_cap->vht_mcs.tx_mcs_map = cpu_to_le16(mcs_map);
	if (ieee80211_hw_check(phy->hw, SUPPORTS_VHT_EXT_NSS_BW))
		vht_cap->vht_mcs.tx_highest |=
				cpu_to_le16(IEEE80211_VHT_EXT_NSS_BW_CAPABLE);
}

void mt76_set_stream_caps(struct mt76_phy *phy, bool vht)
{
	if (phy->cap.has_2ghz)
		mt76_init_stream_cap(phy, &phy->sband_2g.sband, vht);
	if (phy->cap.has_5ghz)
		mt76_init_stream_cap(phy, &phy->sband_5g.sband, vht);
	if (phy->cap.has_6ghz)
		mt76_init_stream_cap(phy, &phy->sband_6g.sband, vht);
}
EXPORT_SYMBOL_GPL(mt76_set_stream_caps);

static int
mt76_init_sband(struct mt76_phy *phy, struct mt76_sband *msband,
		const struct ieee80211_channel *chan, int n_chan,
		struct ieee80211_rate *rates, int n_rates,
		bool ht, bool vht)
{
	struct ieee80211_supported_band *sband = &msband->sband;
	struct ieee80211_sta_vht_cap *vht_cap;
	struct ieee80211_sta_ht_cap *ht_cap;
	struct mt76_dev *dev = phy->dev;
	void *chanlist;
	int size;

	size = n_chan * sizeof(*chan);
	chanlist = devm_kmemdup(dev->dev, chan, size, GFP_KERNEL);
	if (!chanlist)
		return -ENOMEM;

	msband->chan = devm_kcalloc(dev->dev, n_chan, sizeof(*msband->chan),
				    GFP_KERNEL);
	if (!msband->chan)
		return -ENOMEM;

	sband->channels = chanlist;
	sband->n_channels = n_chan;
	sband->bitrates = rates;
	sband->n_bitrates = n_rates;

	if (!ht)
		return 0;

	ht_cap = &sband->ht_cap;
	ht_cap->ht_supported = true;
	ht_cap->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_GRN_FLD |
		       IEEE80211_HT_CAP_SGI_20 |
		       IEEE80211_HT_CAP_SGI_40 |
		       (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);

	ht_cap->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	ht_cap->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;

	mt76_init_stream_cap(phy, sband, vht);

	if (!vht)
		return 0;

	vht_cap = &sband->vht_cap;
	vht_cap->vht_supported = true;
	vht_cap->cap |= IEEE80211_VHT_CAP_RXLDPC |
			IEEE80211_VHT_CAP_RXSTBC_1 |
			IEEE80211_VHT_CAP_SHORT_GI_80 |
			(3 << IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT);

	return 0;
}

static int
mt76_init_sband_2g(struct mt76_phy *phy, struct ieee80211_rate *rates,
		   int n_rates, bool vht)
{
	phy->hw->wiphy->bands[NL80211_BAND_2GHZ] = &phy->sband_2g.sband;

	return mt76_init_sband(phy, &phy->sband_2g, mt76_channels_2ghz,
			       ARRAY_SIZE(mt76_channels_2ghz), rates,
			       n_rates, true, vht);
}

static int
mt76_init_sband_5g(struct mt76_phy *phy, struct ieee80211_rate *rates,
		   int n_rates, bool vht)
{
	phy->hw->wiphy->bands[NL80211_BAND_5GHZ] = &phy->sband_5g.sband;

	return mt76_init_sband(phy, &phy->sband_5g, mt76_channels_5ghz,
			       ARRAY_SIZE(mt76_channels_5ghz), rates,
			       n_rates, true, vht);
}

static int
mt76_init_sband_6g(struct mt76_phy *phy, struct ieee80211_rate *rates,
		   int n_rates)
{
	phy->hw->wiphy->bands[NL80211_BAND_6GHZ] = &phy->sband_6g.sband;

	return mt76_init_sband(phy, &phy->sband_6g, mt76_channels_6ghz,
			       ARRAY_SIZE(mt76_channels_6ghz), rates,
			       n_rates, false, false);
}

static void
mt76_check_sband(struct mt76_phy *phy, struct mt76_sband *msband,
		 enum nl80211_band band)
{
	struct ieee80211_supported_band *sband = &msband->sband;
	bool found = false;
	int i;

	if (!sband)
		return;

	for (i = 0; i < sband->n_channels; i++) {
		if (sband->channels[i].flags & IEEE80211_CHAN_DISABLED)
			continue;

		found = true;
		break;
	}

	if (found) {
		phy->chandef.chan = &sband->channels[0];
		phy->chan_state = &msband->chan[0];
		return;
	}

	sband->n_channels = 0;
	phy->hw->wiphy->bands[band] = NULL;
}

static int
mt76_phy_init(struct mt76_phy *phy, struct ieee80211_hw *hw)
{
	struct mt76_dev *dev = phy->dev;
	struct wiphy *wiphy = hw->wiphy;

	SET_IEEE80211_DEV(hw, dev->dev);
	SET_IEEE80211_PERM_ADDR(hw, phy->macaddr);

	wiphy->features |= NL80211_FEATURE_ACTIVE_MONITOR |
			   NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE;
	wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH |
			WIPHY_FLAG_SUPPORTS_TDLS |
			WIPHY_FLAG_AP_UAPSD;

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);
	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_AIRTIME_FAIRNESS);
	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_AQL);

	wiphy->available_antennas_tx = phy->antenna_mask;
	wiphy->available_antennas_rx = phy->antenna_mask;

	wiphy->sar_capa = &mt76_sar_capa;
	phy->frp = devm_kcalloc(dev->dev, wiphy->sar_capa->num_freq_ranges,
				sizeof(struct mt76_freq_range_power),
				GFP_KERNEL);
	if (!phy->frp)
		return -ENOMEM;

	hw->txq_data_size = sizeof(struct mt76_txq);
	hw->uapsd_max_sp_len = IEEE80211_WMM_IE_STA_QOSINFO_SP_ALL;

	if (!hw->max_tx_fragments)
		hw->max_tx_fragments = 16;

	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, SUPPORTS_RC_TABLE);
	ieee80211_hw_set(hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(hw, SUPPORTS_CLONED_SKBS);
	ieee80211_hw_set(hw, SUPPORTS_AMSDU_IN_AMPDU);
	ieee80211_hw_set(hw, SUPPORTS_REORDERING_BUFFER);

	if (!(dev->drv->drv_flags & MT_DRV_AMSDU_OFFLOAD) &&
	    hw->max_tx_fragments > 1) {
		ieee80211_hw_set(hw, TX_AMSDU);
		ieee80211_hw_set(hw, TX_FRAG_LIST);
	}

	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, AP_LINK_PS);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);

	return 0;
}

struct mt76_phy *
mt76_alloc_phy(struct mt76_dev *dev, unsigned int size,
	       const struct ieee80211_ops *ops, u8 band_idx)
{
	struct ieee80211_hw *hw;
	unsigned int phy_size;
	struct mt76_phy *phy;

	phy_size = ALIGN(sizeof(*phy), 8);
	hw = ieee80211_alloc_hw(size + phy_size, ops);
	if (!hw)
		return NULL;

	phy = hw->priv;
	phy->dev = dev;
	phy->hw = hw;
	phy->priv = hw->priv + phy_size;
	phy->band_idx = band_idx;

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;
	hw->wiphy->interface_modes =
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_AP) |
#ifdef CONFIG_MAC80211_MESH
		BIT(NL80211_IFTYPE_MESH_POINT) |
#endif
		BIT(NL80211_IFTYPE_P2P_CLIENT) |
		BIT(NL80211_IFTYPE_P2P_GO) |
		BIT(NL80211_IFTYPE_ADHOC);

	return phy;
}
EXPORT_SYMBOL_GPL(mt76_alloc_phy);

int mt76_register_phy(struct mt76_phy *phy, bool vht,
		      struct ieee80211_rate *rates, int n_rates)
{
	int ret;

	ret = mt76_phy_init(phy, phy->hw);
	if (ret)
		return ret;

	if (phy->cap.has_2ghz) {
		ret = mt76_init_sband_2g(phy, rates, n_rates, vht);
		if (ret)
			return ret;
	}

	if (phy->cap.has_5ghz) {
		ret = mt76_init_sband_5g(phy, rates + 4, n_rates - 4, vht);
		if (ret)
			return ret;
	}

	if (phy->cap.has_6ghz) {
		ret = mt76_init_sband_6g(phy, rates + 4, n_rates - 4);
		if (ret)
			return ret;
	}

	if (IS_ENABLED(CONFIG_MT76_LEDS)) {
		ret = mt76_led_init(phy);
		if (ret)
			return ret;
	}

	wiphy_read_of_freq_limits(phy->hw->wiphy);
	mt76_check_sband(phy, &phy->sband_2g, NL80211_BAND_2GHZ);
	mt76_check_sband(phy, &phy->sband_5g, NL80211_BAND_5GHZ);
	mt76_check_sband(phy, &phy->sband_6g, NL80211_BAND_6GHZ);

	ret = ieee80211_register_hw(phy->hw);
	if (ret)
		return ret;

	set_bit(MT76_STATE_REGISTERED, &phy->state);
	phy->dev->phys[phy->band_idx] = phy;

	return 0;
}
EXPORT_SYMBOL_GPL(mt76_register_phy);

void mt76_unregister_phy(struct mt76_phy *phy)
{
	struct mt76_dev *dev = phy->dev;

	if (!test_bit(MT76_STATE_REGISTERED, &phy->state))
		return;

	if (IS_ENABLED(CONFIG_MT76_LEDS))
		mt76_led_cleanup(phy);
	mt76_tx_status_check(dev, true);
	ieee80211_unregister_hw(phy->hw);
	dev->phys[phy->band_idx] = NULL;
}
EXPORT_SYMBOL_GPL(mt76_unregister_phy);

int mt76_create_page_pool(struct mt76_dev *dev, struct mt76_queue *q)
{
	struct page_pool_params pp_params = {
		.order = 0,
		.flags = PP_FLAG_PAGE_FRAG,
		.nid = NUMA_NO_NODE,
		.dev = dev->dma_dev,
	};
	int idx = q - dev->q_rx;

	switch (idx) {
	case MT_RXQ_MAIN:
	case MT_RXQ_BAND1:
	case MT_RXQ_BAND2:
		pp_params.pool_size = 256;
		break;
	default:
		pp_params.pool_size = 16;
		break;
	}

	if (mt76_is_mmio(dev)) {
		/* rely on page_pool for DMA mapping */
		pp_params.flags |= PP_FLAG_DMA_MAP | PP_FLAG_DMA_SYNC_DEV;
		pp_params.dma_dir = DMA_FROM_DEVICE;
		pp_params.max_len = PAGE_SIZE;
		pp_params.offset = 0;
	}

	q->page_pool = page_pool_create(&pp_params);
	if (IS_ERR(q->page_pool)) {
		int err = PTR_ERR(q->page_pool);

		q->page_pool = NULL;
		return err;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(mt76_create_page_pool);

struct mt76_dev *
mt76_alloc_device(struct device *pdev, unsigned int size,
		  const struct ieee80211_ops *ops,
		  const struct mt76_driver_ops *drv_ops)
{
	struct ieee80211_hw *hw;
	struct mt76_phy *phy;
	struct mt76_dev *dev;
	int i;

	hw = ieee80211_alloc_hw(size, ops);
	if (!hw)
		return NULL;

	dev = hw->priv;
	dev->hw = hw;
	dev->dev = pdev;
	dev->drv = drv_ops;
	dev->dma_dev = pdev;

	phy = &dev->phy;
	phy->dev = dev;
	phy->hw = hw;
	phy->band_idx = MT_BAND0;
	dev->phys[phy->band_idx] = phy;

	spin_lock_init(&dev->rx_lock);
	spin_lock_init(&dev->lock);
	spin_lock_init(&dev->cc_lock);
	spin_lock_init(&dev->status_lock);
	spin_lock_init(&dev->wed_lock);
	mutex_init(&dev->mutex);
	init_waitqueue_head(&dev->tx_wait);

	skb_queue_head_init(&dev->mcu.res_q);
	init_waitqueue_head(&dev->mcu.wait);
	mutex_init(&dev->mcu.mutex);
	dev->tx_worker.fn = mt76_tx_worker;

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;
	hw->wiphy->interface_modes =
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_AP) |
#ifdef CONFIG_MAC80211_MESH
		BIT(NL80211_IFTYPE_MESH_POINT) |
#endif
		BIT(NL80211_IFTYPE_P2P_CLIENT) |
		BIT(NL80211_IFTYPE_P2P_GO) |
		BIT(NL80211_IFTYPE_ADHOC);

	spin_lock_init(&dev->token_lock);
	idr_init(&dev->token);

	spin_lock_init(&dev->rx_token_lock);
	idr_init(&dev->rx_token);

	INIT_LIST_HEAD(&dev->wcid_list);
	INIT_LIST_HEAD(&dev->sta_poll_list);
	spin_lock_init(&dev->sta_poll_lock);

	INIT_LIST_HEAD(&dev->txwi_cache);
	INIT_LIST_HEAD(&dev->rxwi_cache);
	dev->token_size = dev->drv->token_size;

	for (i = 0; i < ARRAY_SIZE(dev->q_rx); i++)
		skb_queue_head_init(&dev->rx_skb[i]);

	dev->wq = alloc_ordered_workqueue("mt76", 0);
	if (!dev->wq) {
		ieee80211_free_hw(hw);
		return NULL;
	}

	return dev;
}
EXPORT_SYMBOL_GPL(mt76_alloc_device);

int mt76_register_device(struct mt76_dev *dev, bool vht,
			 struct ieee80211_rate *rates, int n_rates)
{
	struct ieee80211_hw *hw = dev->hw;
	struct mt76_phy *phy = &dev->phy;
	int ret;

	dev_set_drvdata(dev->dev, dev);
	ret = mt76_phy_init(phy, hw);
	if (ret)
		return ret;

	if (phy->cap.has_2ghz) {
		ret = mt76_init_sband_2g(phy, rates, n_rates, vht);
		if (ret)
			return ret;
	}

	if (phy->cap.has_5ghz) {
		ret = mt76_init_sband_5g(phy, rates + 4, n_rates - 4, vht);
		if (ret)
			return ret;
	}

	if (phy->cap.has_6ghz) {
		ret = mt76_init_sband_6g(phy, rates + 4, n_rates - 4);
		if (ret)
			return ret;
	}

	wiphy_read_of_freq_limits(hw->wiphy);
	mt76_check_sband(&dev->phy, &phy->sband_2g, NL80211_BAND_2GHZ);
	mt76_check_sband(&dev->phy, &phy->sband_5g, NL80211_BAND_5GHZ);
	mt76_check_sband(&dev->phy, &phy->sband_6g, NL80211_BAND_6GHZ);

	if (IS_ENABLED(CONFIG_MT76_LEDS)) {
		ret = mt76_led_init(phy);
		if (ret)
			return ret;
	}

	ret = ieee80211_register_hw(hw);
	if (ret)
		return ret;

	WARN_ON(mt76_worker_setup(hw, &dev->tx_worker, NULL, "tx"));
	set_bit(MT76_STATE_REGISTERED, &phy->state);
	sched_set_fifo_low(dev->tx_worker.task);

	return 0;
}
EXPORT_SYMBOL_GPL(mt76_register_device);

void mt76_unregister_device(struct mt76_dev *dev)
{
	struct ieee80211_hw *hw = dev->hw;

	if (!test_bit(MT76_STATE_REGISTERED, &dev->phy.state))
		return;

	if (IS_ENABLED(CONFIG_MT76_LEDS))
		mt76_led_cleanup(&dev->phy);
	mt76_tx_status_check(dev, true);
	ieee80211_unregister_hw(hw);
}
EXPORT_SYMBOL_GPL(mt76_unregister_device);

void mt76_free_device(struct mt76_dev *dev)
{
	mt76_worker_teardown(&dev->tx_worker);
	if (dev->wq) {
		destroy_workqueue(dev->wq);
		dev->wq = NULL;
	}
	ieee80211_free_hw(dev->hw);
}
EXPORT_SYMBOL_GPL(mt76_free_device);

static void mt76_rx_release_amsdu(struct mt76_phy *phy, enum mt76_rxq_id q)
{
	struct sk_buff *skb = phy->rx_amsdu[q].head;
	struct mt76_rx_status *status = (struct mt76_rx_status *)skb->cb;
	struct mt76_dev *dev = phy->dev;

	phy->rx_amsdu[q].head = NULL;
	phy->rx_amsdu[q].tail = NULL;

	/*
	 * Validate if the amsdu has a proper first subframe.
	 * A single MSDU can be parsed as A-MSDU when the unauthenticated A-MSDU
	 * flag of the QoS header gets flipped. In such cases, the first
	 * subframe has a LLC/SNAP header in the location of the destination
	 * address.
	 */
	if (skb_shinfo(skb)->frag_list) {
		int offset = 0;

		if (!(status->flag & RX_FLAG_8023)) {
			offset = ieee80211_get_hdrlen_from_skb(skb);

			if ((status->flag &
			     (RX_FLAG_DECRYPTED | RX_FLAG_IV_STRIPPED)) ==
			    RX_FLAG_DECRYPTED)
				offset += 8;
		}

		if (ether_addr_equal(skb->data + offset, rfc1042_header)) {
			dev_kfree_skb(skb);
			return;
		}
	}
	__skb_queue_tail(&dev->rx_skb[q], skb);
}

static void mt76_rx_release_burst(struct mt76_phy *phy, enum mt76_rxq_id q,
				  struct sk_buff *skb)
{
	struct mt76_rx_status *status = (struct mt76_rx_status *)skb->cb;

	if (phy->rx_amsdu[q].head &&
	    (!status->amsdu || status->first_amsdu ||
	     status->seqno != phy->rx_amsdu[q].seqno))
		mt76_rx_release_amsdu(phy, q);

	if (!phy->rx_amsdu[q].head) {
		phy->rx_amsdu[q].tail = &skb_shinfo(skb)->frag_list;
		phy->rx_amsdu[q].seqno = status->seqno;
		phy->rx_amsdu[q].head = skb;
	} else {
		*phy->rx_amsdu[q].tail = skb;
		phy->rx_amsdu[q].tail = &skb->next;
	}

	if (!status->amsdu || status->last_amsdu)
		mt76_rx_release_amsdu(phy, q);
}

void mt76_rx(struct mt76_dev *dev, enum mt76_rxq_id q, struct sk_buff *skb)
{
	struct mt76_rx_status *status = (struct mt76_rx_status *)skb->cb;
	struct mt76_phy *phy = mt76_dev_phy(dev, status->phy_idx);

	if (!test_bit(MT76_STATE_RUNNING, &phy->state)) {
		dev_kfree_skb(skb);
		return;
	}

#ifdef CONFIG_NL80211_TESTMODE
	if (phy->test.state == MT76_TM_STATE_RX_FRAMES) {
		phy->test.rx_stats.packets[q]++;
		if (status->flag & RX_FLAG_FAILED_FCS_CRC)
			phy->test.rx_stats.fcs_error[q]++;
	}
#endif

	mt76_rx_release_burst(phy, q, skb);
}
EXPORT_SYMBOL_GPL(mt76_rx);

bool mt76_has_tx_pending(struct mt76_phy *phy)
{
	struct mt76_queue *q;
	int i;

	for (i = 0; i < __MT_TXQ_MAX; i++) {
		q = phy->q_tx[i];
		if (q && q->queued)
			return true;
	}

	return false;
}
EXPORT_SYMBOL_GPL(mt76_has_tx_pending);

static struct mt76_channel_state *
mt76_channel_state(struct mt76_phy *phy, struct ieee80211_channel *c)
{
	struct mt76_sband *msband;
	int idx;

	if (c->band == NL80211_BAND_2GHZ)
		msband = &phy->sband_2g;
	else if (c->band == NL80211_BAND_6GHZ)
		msband = &phy->sband_6g;
	else
		msband = &phy->sband_5g;

	idx = c - &msband->sband.channels[0];
	return &msband->chan[idx];
}

void mt76_update_survey_active_time(struct mt76_phy *phy, ktime_t time)
{
	struct mt76_channel_state *state = phy->chan_state;

	state->cc_active += ktime_to_us(ktime_sub(time,
						  phy->survey_time));
	phy->survey_time = time;
}
EXPORT_SYMBOL_GPL(mt76_update_survey_active_time);

void mt76_update_survey(struct mt76_phy *phy)
{
	struct mt76_dev *dev = phy->dev;
	ktime_t cur_time;

	if (dev->drv->update_survey)
		dev->drv->update_survey(phy);

	cur_time = ktime_get_boottime();
	mt76_update_survey_active_time(phy, cur_time);

	if (dev->drv->drv_flags & MT_DRV_SW_RX_AIRTIME) {
		struct mt76_channel_state *state = phy->chan_state;

		spin_lock_bh(&dev->cc_lock);
		state->cc_bss_rx += dev->cur_cc_bss_rx;
		dev->cur_cc_bss_rx = 0;
		spin_unlock_bh(&dev->cc_lock);
	}
}
EXPORT_SYMBOL_GPL(mt76_update_survey);

void mt76_set_channel(struct mt76_phy *phy)
{
	struct mt76_dev *dev = phy->dev;
	struct ieee80211_hw *hw = phy->hw;
	struct cfg80211_chan_def *chandef = &hw->conf.chandef;
	bool offchannel = hw->conf.flags & IEEE80211_CONF_OFFCHANNEL;
	int timeout = HZ / 5;

	wait_event_timeout(dev->tx_wait, !mt76_has_tx_pending(phy), timeout);
	mt76_update_survey(phy);

	if (phy->chandef.chan->center_freq != chandef->chan->center_freq ||
	    phy->chandef.width != chandef->width)
		phy->dfs_state = MT_DFS_STATE_UNKNOWN;

	phy->chandef = *chandef;
	phy->chan_state = mt76_channel_state(phy, chandef->chan);

	if (!offchannel)
		phy->main_chan = chandef->chan;

	if (chandef->chan != phy->main_chan)
		memset(phy->chan_state, 0, sizeof(*phy->chan_state));
}
EXPORT_SYMBOL_GPL(mt76_set_channel);

int mt76_get_survey(struct ieee80211_hw *hw, int idx,
		    struct survey_info *survey)
{
	struct mt76_phy *phy = hw->priv;
	struct mt76_dev *dev = phy->dev;
	struct mt76_sband *sband;
	struct ieee80211_channel *chan;
	struct mt76_channel_state *state;
	int ret = 0;

	mutex_lock(&dev->mutex);
	if (idx == 0 && dev->drv->update_survey)
		mt76_update_survey(phy);

	if (idx >= phy->sband_2g.sband.n_channels +
		   phy->sband_5g.sband.n_channels) {
		idx -= (phy->sband_2g.sband.n_channels +
			phy->sband_5g.sband.n_channels);
		sband = &phy->sband_6g;
	} else if (idx >= phy->sband_2g.sband.n_channels) {
		idx -= phy->sband_2g.sband.n_channels;
		sband = &phy->sband_5g;
	} else {
		sband = &phy->sband_2g;
	}

	if (idx >= sband->sband.n_channels) {
		ret = -ENOENT;
		goto out;
	}

	chan = &sband->sband.channels[idx];
	state = mt76_channel_state(phy, chan);

	memset(survey, 0, sizeof(*survey));
	survey->channel = chan;
	survey->filled = SURVEY_INFO_TIME | SURVEY_INFO_TIME_BUSY;
	survey->filled |= dev->drv->survey_flags;
	if (state->noise)
		survey->filled |= SURVEY_INFO_NOISE_DBM;

	if (chan == phy->main_chan) {
		survey->filled |= SURVEY_INFO_IN_USE;

		if (dev->drv->drv_flags & MT_DRV_SW_RX_AIRTIME)
			survey->filled |= SURVEY_INFO_TIME_BSS_RX;
	}

	survey->time_busy = div_u64(state->cc_busy, 1000);
	survey->time_rx = div_u64(state->cc_rx, 1000);
	survey->time = div_u64(state->cc_active, 1000);
	survey->noise = state->noise;

	spin_lock_bh(&dev->cc_lock);
	survey->time_bss_rx = div_u64(state->cc_bss_rx, 1000);
	survey->time_tx = div_u64(state->cc_tx, 1000);
	spin_unlock_bh(&dev->cc_lock);

out:
	mutex_unlock(&dev->mutex);

	return ret;
}
EXPORT_SYMBOL_GPL(mt76_get_survey);

void mt76_wcid_key_setup(struct mt76_dev *dev, struct mt76_wcid *wcid,
			 struct ieee80211_key_conf *key)
{
	struct ieee80211_key_seq seq;
	int i;

	wcid->rx_check_pn = false;

	if (!key)
		return;

	if (key->cipher != WLAN_CIPHER_SUITE_CCMP)
		return;

	wcid->rx_check_pn = true;

	/* data frame */
	for (i = 0; i < IEEE80211_NUM_TIDS; i++) {
		ieee80211_get_key_rx_seq(key, i, &seq);
		memcpy(wcid->rx_key_pn[i], seq.ccmp.pn, sizeof(seq.ccmp.pn));
	}

	/* robust management frame */
	ieee80211_get_key_rx_seq(key, -1, &seq);
	memcpy(wcid->rx_key_pn[i], seq.ccmp.pn, sizeof(seq.ccmp.pn));

}
EXPORT_SYMBOL(mt76_wcid_key_setup);

int mt76_rx_signal(u8 chain_mask, s8 *chain_signal)
{
	int signal = -128;
	u8 chains;

	for (chains = chain_mask; chains; chains >>= 1, chain_signal++) {
		int cur, diff;

		cur = *chain_signal;
		if (!(chains & BIT(0)) ||
		    cur > 0)
			continue;

		if (cur > signal)
			swap(cur, signal);

		diff = signal - cur;
		if (diff == 0)
			signal += 3;
		else if (diff <= 2)
			signal += 2;
		else if (diff <= 6)
			signal += 1;
	}

	return signal;
}
EXPORT_SYMBOL(mt76_rx_signal);

static void
mt76_rx_convert(struct mt76_dev *dev, struct sk_buff *skb,
		struct ieee80211_hw **hw,
		struct ieee80211_sta **sta)
{
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	struct ieee80211_hdr *hdr = mt76_skb_get_hdr(skb);
	struct mt76_rx_status mstat;

	mstat = *((struct mt76_rx_status *)skb->cb);
	memset(status, 0, sizeof(*status));

	status->flag = mstat.flag;
	status->freq = mstat.freq;
	status->enc_flags = mstat.enc_flags;
	status->encoding = mstat.encoding;
	status->bw = mstat.bw;
	status->he_ru = mstat.he_ru;
	status->he_gi = mstat.he_gi;
	status->he_dcm = mstat.he_dcm;
	status->rate_idx = mstat.rate_idx;
	status->nss = mstat.nss;
	status->band = mstat.band;
	status->signal = mstat.signal;
	status->chains = mstat.chains;
	status->ampdu_reference = mstat.ampdu_ref;
	status->device_timestamp = mstat.timestamp;
	status->mactime = mstat.timestamp;
	status->signal = mt76_rx_signal(mstat.chains, mstat.chain_signal);
	if (status->signal <= -128)
		status->flag |= RX_FLAG_NO_SIGNAL_VAL;

	if (ieee80211_is_beacon(hdr->frame_control) ||
	    ieee80211_is_probe_resp(hdr->frame_control))
		status->boottime_ns = ktime_get_boottime_ns();

	BUILD_BUG_ON(sizeof(mstat) > sizeof(skb->cb));
	BUILD_BUG_ON(sizeof(status->chain_signal) !=
		     sizeof(mstat.chain_signal));
	memcpy(status->chain_signal, mstat.chain_signal,
	       sizeof(mstat.chain_signal));

	*sta = wcid_to_sta(mstat.wcid);
	*hw = mt76_phy_hw(dev, mstat.phy_idx);
}

static void
mt76_check_ccmp_pn(struct sk_buff *skb)
{
	struct mt76_rx_status *status = (struct mt76_rx_status *)skb->cb;
	struct mt76_wcid *wcid = status->wcid;
	struct ieee80211_hdr *hdr;
	int security_idx;
	int ret;

	if (!(status->flag & RX_FLAG_DECRYPTED))
		return;

	if (status->flag & RX_FLAG_ONLY_MONITOR)
		return;

	if (!wcid || !wcid->rx_check_pn)
		return;

	security_idx = status->qos_ctl & IEEE80211_QOS_CTL_TID_MASK;
	if (status->flag & RX_FLAG_8023)
		goto skip_hdr_check;

	hdr = mt76_skb_get_hdr(skb);
	if (!(status->flag & RX_FLAG_IV_STRIPPED)) {
		/*
		 * Validate the first fragment both here and in mac80211
		 * All further fragments will be validated by mac80211 only.
		 */
		if (ieee80211_is_frag(hdr) &&
		    !ieee80211_is_first_frag(hdr->frame_control))
			return;
	}

	/* IEEE 802.11-2020, 12.5.3.4.4 "PN and replay detection" c):
	 *
	 * the recipient shall maintain a single replay counter for received
	 * individually addressed robust Management frames that are received
	 * with the To DS subfield equal to 0, [...]
	 */
	if (ieee80211_is_mgmt(hdr->frame_control) &&
	    !ieee80211_has_tods(hdr->frame_control))
		security_idx = IEEE80211_NUM_TIDS;

skip_hdr_check:
	BUILD_BUG_ON(sizeof(status->iv) != sizeof(wcid->rx_key_pn[0]));
	ret = memcmp(status->iv, wcid->rx_key_pn[security_idx],
		     sizeof(status->iv));
	if (ret <= 0) {
		status->flag |= RX_FLAG_ONLY_MONITOR;
		return;
	}

	memcpy(wcid->rx_key_pn[security_idx], status->iv, sizeof(status->iv));

	if (status->flag & RX_FLAG_IV_STRIPPED)
		status->flag |= RX_FLAG_PN_VALIDATED;
}

static void
mt76_airtime_report(struct mt76_dev *dev, struct mt76_rx_status *status,
		    int len)
{
	struct mt76_wcid *wcid = status->wcid;
	struct ieee80211_rx_status info = {
		.enc_flags = status->enc_flags,
		.rate_idx = status->rate_idx,
		.encoding = status->encoding,
		.band = status->band,
		.nss = status->nss,
		.bw = status->bw,
	};
	struct ieee80211_sta *sta;
	u32 airtime;
	u8 tidno = status->qos_ctl & IEEE80211_QOS_CTL_TID_MASK;

	airtime = ieee80211_calc_rx_airtime(dev->hw, &info, len);
	spin_lock(&dev->cc_lock);
	dev->cur_cc_bss_rx += airtime;
	spin_unlock(&dev->cc_lock);

	if (!wcid || !wcid->sta)
		return;

	sta = container_of((void *)wcid, struct ieee80211_sta, drv_priv);
	ieee80211_sta_register_airtime(sta, tidno, 0, airtime);
}

static void
mt76_airtime_flush_ampdu(struct mt76_dev *dev)
{
	struct mt76_wcid *wcid;
	int wcid_idx;

	if (!dev->rx_ampdu_len)
		return;

	wcid_idx = dev->rx_ampdu_status.wcid_idx;
	if (wcid_idx < ARRAY_SIZE(dev->wcid))
		wcid = rcu_dereference(dev->wcid[wcid_idx]);
	else
		wcid = NULL;
	dev->rx_ampdu_status.wcid = wcid;

	mt76_airtime_report(dev, &dev->rx_ampdu_status, dev->rx_ampdu_len);

	dev->rx_ampdu_len = 0;
	dev->rx_ampdu_ref = 0;
}

static void
mt76_airtime_check(struct mt76_dev *dev, struct sk_buff *skb)
{
	struct mt76_rx_status *status = (struct mt76_rx_status *)skb->cb;
	struct mt76_wcid *wcid = status->wcid;

	if (!(dev->drv->drv_flags & MT_DRV_SW_RX_AIRTIME))
		return;

	if (!wcid || !wcid->sta) {
		struct ieee80211_hdr *hdr = mt76_skb_get_hdr(skb);

		if (status->flag & RX_FLAG_8023)
			return;

		if (!ether_addr_equal(hdr->addr1, dev->phy.macaddr))
			return;

		wcid = NULL;
	}

	if (!(status->flag & RX_FLAG_AMPDU_DETAILS) ||
	    status->ampdu_ref != dev->rx_ampdu_ref)
		mt76_airtime_flush_ampdu(dev);

	if (status->flag & RX_FLAG_AMPDU_DETAILS) {
		if (!dev->rx_ampdu_len ||
		    status->ampdu_ref != dev->rx_ampdu_ref) {
			dev->rx_ampdu_status = *status;
			dev->rx_ampdu_status.wcid_idx = wcid ? wcid->idx : 0xff;
			dev->rx_ampdu_ref = status->ampdu_ref;
		}

		dev->rx_ampdu_len += skb->len;
		return;
	}

	mt76_airtime_report(dev, status, skb->len);
}

static void
mt76_check_sta(struct mt76_dev *dev, struct sk_buff *skb)
{
	struct mt76_rx_status *status = (struct mt76_rx_status *)skb->cb;
	struct ieee80211_hdr *hdr = mt76_skb_get_hdr(skb);
	struct ieee80211_sta *sta;
	struct ieee80211_hw *hw;
	struct mt76_wcid *wcid = status->wcid;
	u8 tidno = status->qos_ctl & IEEE80211_QOS_CTL_TID_MASK;
	bool ps;

	hw = mt76_phy_hw(dev, status->phy_idx);
	if (ieee80211_is_pspoll(hdr->frame_control) && !wcid &&
	    !(status->flag & RX_FLAG_8023)) {
		sta = ieee80211_find_sta_by_ifaddr(hw, hdr->addr2, NULL);
		if (sta)
			wcid = status->wcid = (struct mt76_wcid *)sta->drv_priv;
	}

	mt76_airtime_check(dev, skb);

	if (!wcid || !wcid->sta)
		return;

	sta = container_of((void *)wcid, struct ieee80211_sta, drv_priv);

	if (status->signal <= 0)
		ewma_signal_add(&wcid->rssi, -status->signal);

	wcid->inactive_count = 0;

	if (status->flag & RX_FLAG_8023)
		return;

	if (!test_bit(MT_WCID_FLAG_CHECK_PS, &wcid->flags))
		return;

	if (ieee80211_is_pspoll(hdr->frame_control)) {
		ieee80211_sta_pspoll(sta);
		return;
	}

	if (ieee80211_has_morefrags(hdr->frame_control) ||
	    !(ieee80211_is_mgmt(hdr->frame_control) ||
	      ieee80211_is_data(hdr->frame_control)))
		return;

	ps = ieee80211_has_pm(hdr->frame_control);

	if (ps && (ieee80211_is_data_qos(hdr->frame_control) ||
		   ieee80211_is_qos_nullfunc(hdr->frame_control)))
		ieee80211_sta_uapsd_trigger(sta, tidno);

	if (!!test_bit(MT_WCID_FLAG_PS, &wcid->flags) == ps)
		return;

	if (ps)
		set_bit(MT_WCID_FLAG_PS, &wcid->flags);

	if (dev->drv->sta_ps)
		dev->drv->sta_ps(dev, sta, ps);

	if (!ps)
		clear_bit(MT_WCID_FLAG_PS, &wcid->flags);

	ieee80211_sta_ps_transition(sta, ps);
}

void mt76_rx_complete(struct mt76_dev *dev, struct sk_buff_head *frames,
		      struct napi_struct *napi)
{
	struct ieee80211_sta *sta;
	struct ieee80211_hw *hw;
	struct sk_buff *skb, *tmp;
	LIST_HEAD(list);

	spin_lock(&dev->rx_lock);
	while ((skb = __skb_dequeue(frames)) != NULL) {
		struct sk_buff *nskb = skb_shinfo(skb)->frag_list;

		mt76_check_ccmp_pn(skb);
		skb_shinfo(skb)->frag_list = NULL;
		mt76_rx_convert(dev, skb, &hw, &sta);
		ieee80211_rx_list(hw, sta, skb, &list);

		/* subsequent amsdu frames */
		while (nskb) {
			skb = nskb;
			nskb = nskb->next;
			skb->next = NULL;

			mt76_rx_convert(dev, skb, &hw, &sta);
			ieee80211_rx_list(hw, sta, skb, &list);
		}
	}
	spin_unlock(&dev->rx_lock);

	if (!napi) {
		netif_receive_skb_list(&list);
		return;
	}

	list_for_each_entry_safe(skb, tmp, &list, list) {
		skb_list_del_init(skb);
		napi_gro_receive(napi, skb);
	}
}

void mt76_rx_poll_complete(struct mt76_dev *dev, enum mt76_rxq_id q,
			   struct napi_struct *napi)
{
	struct sk_buff_head frames;
	struct sk_buff *skb;

	__skb_queue_head_init(&frames);

	while ((skb = __skb_dequeue(&dev->rx_skb[q])) != NULL) {
		mt76_check_sta(dev, skb);
		if (mtk_wed_device_active(&dev->mmio.wed))
			__skb_queue_tail(&frames, skb);
		else
			mt76_rx_aggr_reorder(skb, &frames);
	}

	mt76_rx_complete(dev, &frames, napi);
}
EXPORT_SYMBOL_GPL(mt76_rx_poll_complete);

static int
mt76_sta_add(struct mt76_phy *phy, struct ieee80211_vif *vif,
	     struct ieee80211_sta *sta)
{
	struct mt76_wcid *wcid = (struct mt76_wcid *)sta->drv_priv;
	struct mt76_dev *dev = phy->dev;
	int ret;
	int i;

	mutex_lock(&dev->mutex);

	ret = dev->drv->sta_add(dev, vif, sta);
	if (ret)
		goto out;

	for (i = 0; i < ARRAY_SIZE(sta->txq); i++) {
		struct mt76_txq *mtxq;

		if (!sta->txq[i])
			continue;

		mtxq = (struct mt76_txq *)sta->txq[i]->drv_priv;
		mtxq->wcid = wcid->idx;
	}

	ewma_signal_init(&wcid->rssi);
	if (phy->band_idx == MT_BAND1)
		mt76_wcid_mask_set(dev->wcid_phy_mask, wcid->idx);
	wcid->phy_idx = phy->band_idx;
	rcu_assign_pointer(dev->wcid[wcid->idx], wcid);

	mt76_packet_id_init(wcid);
out:
	mutex_unlock(&dev->mutex);

	return ret;
}

void __mt76_sta_remove(struct mt76_dev *dev, struct ieee80211_vif *vif,
		       struct ieee80211_sta *sta)
{
	struct mt76_wcid *wcid = (struct mt76_wcid *)sta->drv_priv;
	int i, idx = wcid->idx;

	for (i = 0; i < ARRAY_SIZE(wcid->aggr); i++)
		mt76_rx_aggr_stop(dev, wcid, i);

	if (dev->drv->sta_remove)
		dev->drv->sta_remove(dev, vif, sta);

	mt76_packet_id_flush(dev, wcid);

	mt76_wcid_mask_clear(dev->wcid_mask, idx);
	mt76_wcid_mask_clear(dev->wcid_phy_mask, idx);
}
EXPORT_SYMBOL_GPL(__mt76_sta_remove);

static void
mt76_sta_remove(struct mt76_dev *dev, struct ieee80211_vif *vif,
		struct ieee80211_sta *sta)
{
	mutex_lock(&dev->mutex);
	__mt76_sta_remove(dev, vif, sta);
	mutex_unlock(&dev->mutex);
}

int mt76_sta_state(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		   struct ieee80211_sta *sta,
		   enum ieee80211_sta_state old_state,
		   enum ieee80211_sta_state new_state)
{
	struct mt76_phy *phy = hw->priv;
	struct mt76_dev *dev = phy->dev;

	if (old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE)
		return mt76_sta_add(phy, vif, sta);

	if (old_state == IEEE80211_STA_AUTH &&
	    new_state == IEEE80211_STA_ASSOC &&
	    dev->drv->sta_assoc)
		dev->drv->sta_assoc(dev, vif, sta);

	if (old_state == IEEE80211_STA_NONE &&
	    new_state == IEEE80211_STA_NOTEXIST)
		mt76_sta_remove(dev, vif, sta);

	return 0;
}
EXPORT_SYMBOL_GPL(mt76_sta_state);

void mt76_sta_pre_rcu_remove(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			     struct ieee80211_sta *sta)
{
	struct mt76_phy *phy = hw->priv;
	struct mt76_dev *dev = phy->dev;
	struct mt76_wcid *wcid = (struct mt76_wcid *)sta->drv_priv;

	mutex_lock(&dev->mutex);
	spin_lock_bh(&dev->status_lock);
	rcu_assign_pointer(dev->wcid[wcid->idx], NULL);
	spin_unlock_bh(&dev->status_lock);
	mutex_unlock(&dev->mutex);
}
EXPORT_SYMBOL_GPL(mt76_sta_pre_rcu_remove);

int mt76_get_txpower(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		     int *dbm)
{
	struct mt76_phy *phy = hw->priv;
	int n_chains = hweight8(phy->antenna_mask);
	int delta = mt76_tx_power_nss_delta(n_chains);

	*dbm = DIV_ROUND_UP(phy->txpower_cur + delta, 2);

	return 0;
}
EXPORT_SYMBOL_GPL(mt76_get_txpower);

int mt76_init_sar_power(struct ieee80211_hw *hw,
			const struct cfg80211_sar_specs *sar)
{
	struct mt76_phy *phy = hw->priv;
	const struct cfg80211_sar_capa *capa = hw->wiphy->sar_capa;
	int i;

	if (sar->type != NL80211_SAR_TYPE_POWER || !sar->num_sub_specs)
		return -EINVAL;

	for (i = 0; i < sar->num_sub_specs; i++) {
		u32 index = sar->sub_specs[i].freq_range_index;
		/* SAR specifies power limitaton in 0.25dbm */
		s32 power = sar->sub_specs[i].power >> 1;

		if (power > 127 || power < -127)
			power = 127;

		phy->frp[index].range = &capa->freq_ranges[index];
		phy->frp[index].power = power;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(mt76_init_sar_power);

int mt76_get_sar_power(struct mt76_phy *phy,
		       struct ieee80211_channel *chan,
		       int power)
{
	const struct cfg80211_sar_capa *capa = phy->hw->wiphy->sar_capa;
	int freq, i;

	if (!capa || !phy->frp)
		return power;

	if (power > 127 || power < -127)
		power = 127;

	freq = ieee80211_channel_to_frequency(chan->hw_value, chan->band);
	for (i = 0 ; i < capa->num_freq_ranges; i++) {
		if (phy->frp[i].range &&
		    freq >= phy->frp[i].range->start_freq &&
		    freq < phy->frp[i].range->end_freq) {
			power = min_t(int, phy->frp[i].power, power);
			break;
		}
	}

	return power;
}
EXPORT_SYMBOL_GPL(mt76_get_sar_power);

static void
__mt76_csa_finish(void *priv, u8 *mac, struct ieee80211_vif *vif)
{
	if (vif->bss_conf.csa_active && ieee80211_beacon_cntdwn_is_complete(vif))
		ieee80211_csa_finish(vif);
}

void mt76_csa_finish(struct mt76_dev *dev)
{
	if (!dev->csa_complete)
		return;

	ieee80211_iterate_active_interfaces_atomic(dev->hw,
		IEEE80211_IFACE_ITER_RESUME_ALL,
		__mt76_csa_finish, dev);

	dev->csa_complete = 0;
}
EXPORT_SYMBOL_GPL(mt76_csa_finish);

static void
__mt76_csa_check(void *priv, u8 *mac, struct ieee80211_vif *vif)
{
	struct mt76_dev *dev = priv;

	if (!vif->bss_conf.csa_active)
		return;

	dev->csa_complete |= ieee80211_beacon_cntdwn_is_complete(vif);
}

void mt76_csa_check(struct mt76_dev *dev)
{
	ieee80211_iterate_active_interfaces_atomic(dev->hw,
		IEEE80211_IFACE_ITER_RESUME_ALL,
		__mt76_csa_check, dev);
}
EXPORT_SYMBOL_GPL(mt76_csa_check);

int
mt76_set_tim(struct ieee80211_hw *hw, struct ieee80211_sta *sta, bool set)
{
	return 0;
}
EXPORT_SYMBOL_GPL(mt76_set_tim);

void mt76_insert_ccmp_hdr(struct sk_buff *skb, u8 key_id)
{
	struct mt76_rx_status *status = (struct mt76_rx_status *)skb->cb;
	int hdr_len = ieee80211_get_hdrlen_from_skb(skb);
	u8 *hdr, *pn = status->iv;

	__skb_push(skb, 8);
	memmove(skb->data, skb->data + 8, hdr_len);
	hdr = skb->data + hdr_len;

	hdr[0] = pn[5];
	hdr[1] = pn[4];
	hdr[2] = 0;
	hdr[3] = 0x20 | (key_id << 6);
	hdr[4] = pn[3];
	hdr[5] = pn[2];
	hdr[6] = pn[1];
	hdr[7] = pn[0];

	status->flag &= ~RX_FLAG_IV_STRIPPED;
}
EXPORT_SYMBOL_GPL(mt76_insert_ccmp_hdr);

int mt76_get_rate(struct mt76_dev *dev,
		  struct ieee80211_supported_band *sband,
		  int idx, bool cck)
{
	int i, offset = 0, len = sband->n_bitrates;

	if (cck) {
		if (sband != &dev->phy.sband_2g.sband)
			return 0;

		idx &= ~BIT(2); /* short preamble */
	} else if (sband == &dev->phy.sband_2g.sband) {
		offset = 4;
	}

	for (i = offset; i < len; i++) {
		if ((sband->bitrates[i].hw_value & GENMASK(7, 0)) == idx)
			return i;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(mt76_get_rate);

void mt76_sw_scan(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		  const u8 *mac)
{
	struct mt76_phy *phy = hw->priv;

	set_bit(MT76_SCANNING, &phy->state);
}
EXPORT_SYMBOL_GPL(mt76_sw_scan);

void mt76_sw_scan_complete(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct mt76_phy *phy = hw->priv;

	clear_bit(MT76_SCANNING, &phy->state);
}
EXPORT_SYMBOL_GPL(mt76_sw_scan_complete);

int mt76_get_antenna(struct ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
{
	struct mt76_phy *phy = hw->priv;
	struct mt76_dev *dev = phy->dev;

	mutex_lock(&dev->mutex);
	*tx_ant = phy->antenna_mask;
	*rx_ant = phy->antenna_mask;
	mutex_unlock(&dev->mutex);

	return 0;
}
EXPORT_SYMBOL_GPL(mt76_get_antenna);

struct mt76_queue *
mt76_init_queue(struct mt76_dev *dev, int qid, int idx, int n_desc,
		int ring_base, u32 flags)
{
	struct mt76_queue *hwq;
	int err;

	hwq = devm_kzalloc(dev->dev, sizeof(*hwq), GFP_KERNEL);
	if (!hwq)
		return ERR_PTR(-ENOMEM);

	hwq->flags = flags;

	err = dev->queue_ops->alloc(dev, hwq, idx, n_desc, 0, ring_base);
	if (err < 0)
		return ERR_PTR(err);

	return hwq;
}
EXPORT_SYMBOL_GPL(mt76_init_queue);

u16 mt76_calculate_default_rate(struct mt76_phy *phy, int rateidx)
{
	int offset = 0;

	if (phy->chandef.chan->band != NL80211_BAND_2GHZ)
		offset = 4;

	/* pick the lowest rate for hidden nodes */
	if (rateidx < 0)
		rateidx = 0;

	rateidx += offset;
	if (rateidx >= ARRAY_SIZE(mt76_rates))
		rateidx = offset;

	return mt76_rates[rateidx].hw_value;
}
EXPORT_SYMBOL_GPL(mt76_calculate_default_rate);

void mt76_ethtool_worker(struct mt76_ethtool_worker_info *wi,
			 struct mt76_sta_stats *stats, bool eht)
{
	int i, ei = wi->initial_stat_idx;
	u64 *data = wi->data;

	wi->sta_count++;

	data[ei++] += stats->tx_mode[MT_PHY_TYPE_CCK];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_OFDM];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HT];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HT_GF];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_VHT];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HE_SU];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HE_EXT_SU];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HE_TB];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HE_MU];
	if (eht) {
		data[ei++] += stats->tx_mode[MT_PHY_TYPE_EHT_SU];
		data[ei++] += stats->tx_mode[MT_PHY_TYPE_EHT_TRIG];
		data[ei++] += stats->tx_mode[MT_PHY_TYPE_EHT_MU];
	}

	for (i = 0; i < (ARRAY_SIZE(stats->tx_bw) - !eht); i++)
		data[ei++] += stats->tx_bw[i];

	for (i = 0; i < (eht ? 14 : 12); i++)
		data[ei++] += stats->tx_mcs[i];

	for (i = 0; i < 4; i++)
		data[ei++] += stats->tx_nss[i];

	wi->worker_stat_count = ei - wi->initial_stat_idx;
}
EXPORT_SYMBOL_GPL(mt76_ethtool_worker);

void mt76_ethtool_page_pool_stats(struct mt76_dev *dev, u64 *data, int *index)
{
#ifdef CONFIG_PAGE_POOL_STATS
	struct page_pool_stats stats = {};
	int i;

	mt76_for_each_q_rx(dev, i)
		page_pool_get_stats(dev->q_rx[i].page_pool, &stats);

	page_pool_ethtool_stats_get(data, &stats);
	*index += page_pool_ethtool_stats_get_count();
#endif
}
EXPORT_SYMBOL_GPL(mt76_ethtool_page_pool_stats);

enum mt76_dfs_state mt76_phy_dfs_state(struct mt76_phy *phy)
{
	struct ieee80211_hw *hw = phy->hw;
	struct mt76_dev *dev = phy->dev;

	if (dev->region == NL80211_DFS_UNSET ||
	    test_bit(MT76_SCANNING, &phy->state))
		return MT_DFS_STATE_DISABLED;

	if (!hw->conf.radar_enabled) {
		if ((hw->conf.flags & IEEE80211_CONF_MONITOR) &&
		    (phy->chandef.chan->flags & IEEE80211_CHAN_RADAR))
			return MT_DFS_STATE_ACTIVE;

		return MT_DFS_STATE_DISABLED;
	}

	if (!cfg80211_reg_can_beacon(hw->wiphy, &phy->chandef, NL80211_IFTYPE_AP))
		return MT_DFS_STATE_CAC;

	return MT_DFS_STATE_ACTIVE;
}
EXPORT_SYMBOL_GPL(mt76_phy_dfs_state);
