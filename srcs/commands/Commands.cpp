
#include "Commands.hpp"
#include "Debug.hpp"
#include "Channel.hpp"
#include "Answers.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Commands::Commands()
{
	start;
	cmd_map.insert(std::make_pair("NICK", &Commands::nick));
	cmd_map.insert(std::make_pair("USER", &Commands::setUser));
	cmd_map.insert(std::make_pair("JOIN", &Commands::join));
	cmd_map.insert(std::make_pair("PRIVMSG", &Commands::priv_msg));
	cmd_map.insert(std::make_pair("EXIT", &Commands::quit_s));
	cmd_map.insert(std::make_pair("INVITE", &Commands::invite));
	cmd_map.insert(std::make_pair("PART", &Commands::part));
	cmd_map.insert(std::make_pair("TOPIC", &Commands::topic));
	cmd_map.insert(std::make_pair("NAMES", &Commands::names));
	cmd_map.insert(std::make_pair("LIST", &Commands::list));
	cmd_map.insert(std::make_pair("MODE", &Commands::mode));
	cmd_map.insert(std::make_pair("KICK", &Commands::kick));
	cmd_map.insert(std::make_pair("WHOIS", &Commands::whois));
	cmd_map.insert(std::make_pair("OPER", &Commands::oper));
	cmd_map.insert(std::make_pair("NOTICE", &Commands::notice));


	// Now storing replies ; idee, ptr sur func genre Answer::&RPL_001   avec RPL 001 qui prendra un user
	server_replies.insert(std::make_pair(001, &RPL_001));
	server_replies.insert(std::make_pair(002, &RPL_002));
	server_replies.insert(std::make_pair(003, &RPL_003));
	server_replies.insert(std::make_pair(004, &RPL_004));
	server_replies.insert(std::make_pair(004, &RPL_004));
	server_replies.insert(std::make_pair(005, &RPL_005));
	server_replies.insert(std::make_pair(200, &RPL_200));
	server_replies.insert(std::make_pair(201, &RPL_201));
	server_replies.insert(std::make_pair(202, &RPL_202));
	server_replies.insert(std::make_pair(203, &RPL_203));
	server_replies.insert(std::make_pair(204, &RPL_204));
	server_replies.insert(std::make_pair(205, &RPL_205));
	server_replies.insert(std::make_pair(206, &RPL_206));
	server_replies.insert(std::make_pair(207, &RPL_207));
	server_replies.insert(std::make_pair(208, &RPL_208));
	server_replies.insert(std::make_pair(209, &RPL_209));
	server_replies.insert(std::make_pair(210, &RPL_210));
	server_replies.insert(std::make_pair(211, &RPL_211));
	server_replies.insert(std::make_pair(212, &RPL_212));
	server_replies.insert(std::make_pair(213, &RPL_213));
	server_replies.insert(std::make_pair(214, &RPL_214));
	server_replies.insert(std::make_pair(215, &RPL_215));
	server_replies.insert(std::make_pair(216, &RPL_216));
	server_replies.insert(std::make_pair(217, &RPL_217));
	server_replies.insert(std::make_pair(218, &RPL_218));
	server_replies.insert(std::make_pair(219, &RPL_219));
	server_replies.insert(std::make_pair(221, &RPL_221));
	server_replies.insert(std::make_pair(231, &RPL_231));
	server_replies.insert(std::make_pair(232, &RPL_232));
	server_replies.insert(std::make_pair(233, &RPL_233));
	server_replies.insert(std::make_pair(234, &RPL_234));
	server_replies.insert(std::make_pair(235, &RPL_235));
	server_replies.insert(std::make_pair(240, &RPL_240));
	server_replies.insert(std::make_pair(241, &RPL_241));
	server_replies.insert(std::make_pair(242, &RPL_242));
	server_replies.insert(std::make_pair(243, &RPL_243));
	server_replies.insert(std::make_pair(244, &RPL_244));
	server_replies.insert(std::make_pair(246, &RPL_246));
	server_replies.insert(std::make_pair(247, &RPL_247));
	server_replies.insert(std::make_pair(249, &RPL_249));
	server_replies.insert(std::make_pair(250, &RPL_250));
	server_replies.insert(std::make_pair(251, &RPL_251));
	server_replies.insert(std::make_pair(252, &RPL_252));
	server_replies.insert(std::make_pair(253, &RPL_253));
	server_replies.insert(std::make_pair(254, &RPL_254));
	server_replies.insert(std::make_pair(255, &RPL_255));
	server_replies.insert(std::make_pair(256, &RPL_256));
	server_replies.insert(std::make_pair(257, &RPL_257));
	server_replies.insert(std::make_pair(258, &RPL_258));
	server_replies.insert(std::make_pair(259, &RPL_259));
	server_replies.insert(std::make_pair(261, &RPL_261));
	server_replies.insert(std::make_pair(262, &RPL_262));
	server_replies.insert(std::make_pair(262, &RPL_262));
	server_replies.insert(std::make_pair(263, &RPL_263));
	server_replies.insert(std::make_pair(300, &RPL_300));
	server_replies.insert(std::make_pair(301, &RPL_301));
	server_replies.insert(std::make_pair(302, &RPL_302));
	server_replies.insert(std::make_pair(303, &RPL_303));
	server_replies.insert(std::make_pair(305, &RPL_305));
	server_replies.insert(std::make_pair(306, &RPL_306));
	server_replies.insert(std::make_pair(311, &RPL_311));
	server_replies.insert(std::make_pair(312, &RPL_312));
	server_replies.insert(std::make_pair(313, &RPL_313));
	server_replies.insert(std::make_pair(314, &RPL_314));
	server_replies.insert(std::make_pair(315, &RPL_315));
	server_replies.insert(std::make_pair(316, &RPL_316));
	server_replies.insert(std::make_pair(317, &RPL_317));
	server_replies.insert(std::make_pair(318, &RPL_318));
	server_replies.insert(std::make_pair(319, &RPL_319));
	server_replies.insert(std::make_pair(322, &RPL_322));
	server_replies.insert(std::make_pair(323, &RPL_323));
	server_replies.insert(std::make_pair(324, &RPL_324));
	server_replies.insert(std::make_pair(325, &RPL_325));
	server_replies.insert(std::make_pair(331, &RPL_331));
	server_replies.insert(std::make_pair(332, &RPL_332));
	server_replies.insert(std::make_pair(341, &RPL_341));
	server_replies.insert(std::make_pair(342, &RPL_342));
	server_replies.insert(std::make_pair(346, &RPL_346));
	server_replies.insert(std::make_pair(347, &RPL_347));
	server_replies.insert(std::make_pair(348, &RPL_348));
	server_replies.insert(std::make_pair(349, &RPL_349));
	server_replies.insert(std::make_pair(351, &RPL_351));
	server_replies.insert(std::make_pair(352, &RPL_352));
	server_replies.insert(std::make_pair(353, &RPL_353));
	server_replies.insert(std::make_pair(354, &RPL_354));
	server_replies.insert(std::make_pair(361, &RPL_361));
	server_replies.insert(std::make_pair(362, &RPL_362));
	server_replies.insert(std::make_pair(363, &RPL_363));
	server_replies.insert(std::make_pair(364, &RPL_364));
	server_replies.insert(std::make_pair(365, &RPL_365));
	server_replies.insert(std::make_pair(366, &RPL_366));
	server_replies.insert(std::make_pair(367, &RPL_367));
	server_replies.insert(std::make_pair(368, &RPL_368));
	server_replies.insert(std::make_pair(369, &RPL_369));
	server_replies.insert(std::make_pair(371, &RPL_371));
	server_replies.insert(std::make_pair(372, &RPL_372));
	server_replies.insert(std::make_pair(373, &RPL_373));
	server_replies.insert(std::make_pair(374, &RPL_374));
	server_replies.insert(std::make_pair(375, &RPL_375));
	server_replies.insert(std::make_pair(376, &RPL_376));
	server_replies.insert(std::make_pair(381, &RPL_381));
	server_replies.insert(std::make_pair(382, &RPL_382));
	server_replies.insert(std::make_pair(383, &RPL_383));
	server_replies.insert(std::make_pair(384, &RPL_384));
	server_replies.insert(std::make_pair(391, &RPL_391));
	server_replies.insert(std::make_pair(392, &RPL_392));
	server_replies.insert(std::make_pair(393, &RPL_393));
	server_replies.insert(std::make_pair(394, &RPL_394));
	server_replies.insert(std::make_pair(395, &RPL_395));
	server_replies.insert(std::make_pair(401, &RPL_401));
	server_replies.insert(std::make_pair(402, &RPL_402));
	server_replies.insert(std::make_pair(403, &RPL_403));
	server_replies.insert(std::make_pair(404, &RPL_404));
	server_replies.insert(std::make_pair(405, &RPL_405));
	server_replies.insert(std::make_pair(406, &RPL_406));
	server_replies.insert(std::make_pair(407, &RPL_407));
	server_replies.insert(std::make_pair(408, &RPL_408));
	server_replies.insert(std::make_pair(409, &RPL_409));
	server_replies.insert(std::make_pair(411, &RPL_411));
	server_replies.insert(std::make_pair(412, &RPL_412));
	server_replies.insert(std::make_pair(413, &RPL_413));
	server_replies.insert(std::make_pair(414, &RPL_414));
	server_replies.insert(std::make_pair(415, &RPL_415));
	server_replies.insert(std::make_pair(421, &RPL_421));
	server_replies.insert(std::make_pair(422, &RPL_422));
	server_replies.insert(std::make_pair(423, &RPL_423));
	server_replies.insert(std::make_pair(424, &RPL_424));
	server_replies.insert(std::make_pair(431, &RPL_431));
	server_replies.insert(std::make_pair(432, &RPL_432));
	server_replies.insert(std::make_pair(433, &RPL_433));
	server_replies.insert(std::make_pair(436, &RPL_436));
	server_replies.insert(std::make_pair(437, &RPL_437));
	server_replies.insert(std::make_pair(441, &RPL_441));
	server_replies.insert(std::make_pair(442, &RPL_442));
	server_replies.insert(std::make_pair(443, &RPL_443));
	server_replies.insert(std::make_pair(444, &RPL_444));
	server_replies.insert(std::make_pair(445, &RPL_445));
	server_replies.insert(std::make_pair(446, &RPL_446));
	server_replies.insert(std::make_pair(451, &RPL_451));
	server_replies.insert(std::make_pair(461, &RPL_461));
	server_replies.insert(std::make_pair(462, &RPL_462));
	server_replies.insert(std::make_pair(463, &RPL_463));
	server_replies.insert(std::make_pair(464, &RPL_464));
	server_replies.insert(std::make_pair(465, &RPL_465));
	server_replies.insert(std::make_pair(466, &RPL_466));
	server_replies.insert(std::make_pair(467, &RPL_467));
	server_replies.insert(std::make_pair(471, &RPL_471));
	server_replies.insert(std::make_pair(472, &RPL_472));
	server_replies.insert(std::make_pair(473, &RPL_473));
	server_replies.insert(std::make_pair(474, &RPL_474));
	server_replies.insert(std::make_pair(475, &RPL_475));
	server_replies.insert(std::make_pair(476, &RPL_476));
	server_replies.insert(std::make_pair(477, &RPL_477));
	server_replies.insert(std::make_pair(478, &RPL_478));
	server_replies.insert(std::make_pair(481, &RPL_481));
	server_replies.insert(std::make_pair(482, &RPL_482));
	server_replies.insert(std::make_pair(483, &RPL_483));
	server_replies.insert(std::make_pair(484, &RPL_484));
	server_replies.insert(std::make_pair(485, &RPL_485));
	server_replies.insert(std::make_pair(491, &RPL_491));
	server_replies.insert(std::make_pair(492, &RPL_492));
	server_replies.insert(std::make_pair(501, &RPL_501));
	server_replies.insert(std::make_pair(502, &RPL_502));
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Commands::~Commands()
{
}
