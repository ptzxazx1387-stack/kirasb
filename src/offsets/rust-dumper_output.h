inline static constexpr uintptr_t il2cpphandle = 0x101CA4E0;
struct base_networkable
{
	inline static constexpr uintptr_t base_address = 0xFD36298;
	inline static constexpr uintptr_t static_fields = 0xb8;
	inline static constexpr uintptr_t wrapper_class_ptr = 0x0;
	inline static constexpr uintptr_t parent_static_fields = 0x10;
	inline static constexpr uintptr_t entities = 0x10;
	inline static constexpr uintptr_t hv_offset = 0x18;
};
struct camera
{
	inline static constexpr uintptr_t main_camera_c = 0xFD0A5C0;
	inline static constexpr uintptr_t camera_static = 0xb8;
	inline static constexpr uintptr_t camera_object = 0x0;
	inline static constexpr uintptr_t entity = 0x10;
	inline static constexpr uintptr_t view_matrix = 0x2fc; //Unity native camera state
	inline static constexpr uintptr_t position = 0x444; //Unity native camera state
	inline static constexpr uintptr_t field_of_view = 0x170; //Unity native camera state
	inline static constexpr uintptr_t culling_mask = 0x3e8; //Unity native camera state
};
struct base_player
{
	inline static constexpr uintptr_t cl_active_item = 0x568;
	inline static constexpr uintptr_t player_eyes = 0x3e8;
	inline static constexpr uintptr_t player_inventory = 0x2f0;
	inline static constexpr uintptr_t current_team = 0x538;
	inline static constexpr uintptr_t base_movement = 0x788;
	inline static constexpr uintptr_t player_model = 0x500;
	inline static constexpr uintptr_t player_flags = 0x6b8;
	inline static constexpr uintptr_t display_name = 0x6e0;
	inline static constexpr uintptr_t player_input = 0x518;
};
struct base_combat_entity
{
	inline static constexpr uintptr_t lifestate = 0x298;
	inline static constexpr uintptr_t model = 0x1a8;
	inline static constexpr uintptr_t _health = 0x2a4;
	inline static constexpr uintptr_t _maxHealth = 0x2a8;
};
struct base_entity
{
	inline static constexpr uintptr_t flags = 0x1b0;
};
struct item_container
{
	inline static constexpr uintptr_t item_list = 0x18;
};
struct player_inventory
{
	inline static constexpr uintptr_t main = 0x30;
	inline static constexpr uintptr_t belt = 0x60;
	inline static constexpr uintptr_t wear = 0x28;
};
struct item
{
	inline static constexpr uintptr_t definition = 0xa0;
	inline static constexpr uintptr_t amount = 0xe0;
	inline static constexpr uintptr_t uid = 0x60;
	inline static constexpr uintptr_t held_entity = 0x0;
};
struct item_definition
{
	inline static constexpr uintptr_t itemid = 0x20;
	inline static constexpr uintptr_t shortname = 0x28;
	inline static constexpr uintptr_t displayName = 0x40;
	inline static constexpr uintptr_t category = 0x58;
	inline static constexpr uintptr_t stackable = 0x78;
	inline static constexpr uintptr_t iconSprite = 0x50;
	inline static constexpr uintptr_t rarity = 0x94;
	inline static constexpr uintptr_t condition = 0xb8;
};
struct base_projectile
{
	inline static constexpr uintptr_t projectileVelocityScale = 0x37c;
	inline static constexpr uintptr_t automatic = 0x380;
	inline static constexpr uintptr_t reloadTime = 0x3c0;
	inline static constexpr uintptr_t primaryMagazine = 0x3c8;
	inline static constexpr uintptr_t aimSway = 0x3e8;
	inline static constexpr uintptr_t aimSwaySpeed = 0x3ec;
	inline static constexpr uintptr_t recoil = 0x3f0;
	inline static constexpr uintptr_t aimCone = 0x400;
	inline static constexpr uintptr_t hipAimCone = 0x404;
	inline static constexpr uintptr_t aimconePenaltyPerShot = 0x408;
	inline static constexpr uintptr_t stancePenaltyScale = 0x418;
	inline static constexpr uintptr_t hasADS = 0x41c;
	inline static constexpr uintptr_t isBurstWeapon = 0x427;
	inline static constexpr uintptr_t canChangeFireModes = 0x428;
	inline static constexpr uintptr_t internalBurstFireRateScale = 0x430;
	inline static constexpr uintptr_t internalBurstAimConeScale = 0x434;
	inline static constexpr uintptr_t canUnloadAmmo = 0x3c4;
	inline static constexpr uintptr_t fractionalReload = 0x3d0;
};
struct recoil_properties
{
	inline static constexpr uintptr_t recoilYawMin = 0x18;
	inline static constexpr uintptr_t recoilYawMax = 0x1c;
	inline static constexpr uintptr_t recoilPitchMin = 0x20;
	inline static constexpr uintptr_t recoilPitchMax = 0x24;
	inline static constexpr uintptr_t timeToTakeMin = 0x28;
	inline static constexpr uintptr_t timeToTakeMax = 0x2c;
	inline static constexpr uintptr_t ADSScale = 0x30;
	inline static constexpr uintptr_t movementPenalty = 0x34;
	inline static constexpr uintptr_t clampPitch = 0x38;
	inline static constexpr uintptr_t pitchCurve = 0x40;
	inline static constexpr uintptr_t yawCurve = 0x48;
	inline static constexpr uintptr_t useCurves = 0x50;
	inline static constexpr uintptr_t shotsUntilMax = 0x54;
	inline static constexpr uintptr_t maxRecoilRadius = 0x58;
	inline static constexpr uintptr_t overrideAimconeWithCurve = 0x5c;
	inline static constexpr uintptr_t aimconeCurveScale = 0x60;
	inline static constexpr uintptr_t aimconeCurve = 0x68;
	inline static constexpr uintptr_t aimconeProbabilityCurve = 0x70;
	inline static constexpr uintptr_t newRecoilOverride = 0x80;
};
struct world_item
{
	inline static constexpr uintptr_t allowPickup = 0x1f0;
	inline static constexpr uintptr_t item = 0x1f8;
};
struct held_entity
{
	inline static constexpr uintptr_t viewModel = 0x240;
	inline static constexpr uintptr_t worldModelAnimator = 0x208;
	inline static constexpr uintptr_t handBone = 0x250;
	inline static constexpr uintptr_t holdInfo = 0x260;
	inline static constexpr uintptr_t isBuildingTool = 0x27c;
	inline static constexpr uintptr_t forcedOwner = 0x280;
	inline static constexpr uintptr_t hostileScore = 0x29c;
	inline static constexpr uintptr_t item_owner = 0x1f0;
	inline static constexpr uintptr_t ownerItemUID = 0x2d0;
};
struct model
{
	inline static constexpr uintptr_t collision = 0x20;
	inline static constexpr uintptr_t rootBone = 0x28;
	inline static constexpr uintptr_t headBone = 0x30;
	inline static constexpr uintptr_t eyeBone = 0x38;
	inline static constexpr uintptr_t animator = 0x40;
	inline static constexpr uintptr_t skeleton = 0x48;
	inline static constexpr uintptr_t boneTransforms = 0x50;
	inline static constexpr uintptr_t boneNames = 0x58;
};
struct player_model
{
	inline static constexpr uintptr_t jawBone = 0xe8;
	inline static constexpr uintptr_t neckBone = 0xf0;
	inline static constexpr uintptr_t headBone = 0xf8;
	inline static constexpr uintptr_t skinnedMultiMesh = 0x398;
	inline static constexpr uintptr_t position = 0x498; //heuristic — last-pair Vector3
	inline static constexpr uintptr_t velocity = 0x4fc; //heuristic — last-pair Vector3
};
struct player_eyes
{
	inline static constexpr uintptr_t viewOffset = 0x60;
	inline static constexpr uintptr_t bodyRotation = 0x50;
	inline static constexpr uintptr_t worldPosition = 0x0;
};
struct player_input
{
	inline static constexpr uintptr_t bodyAngles = 0x44;
};
struct player_walk_movement
{
	inline static constexpr uintptr_t GroundAngle = 0x70; //hardcoded — reverify
	inline static constexpr uintptr_t GroundAngleNew = 0x78; //hardcoded — reverify
	inline static constexpr uintptr_t GroundTime = 0x80; //hardcoded — reverify
	inline static constexpr uintptr_t JumpTime = 0x88; //hardcoded — reverify
	inline static constexpr uintptr_t LandTime = 0x90; //hardcoded — reverify
	inline static constexpr uintptr_t GravityMultiplier = 0x98; //hardcoded — reverify
	inline static constexpr uintptr_t TargetMovement = 0x128; //hardcoded — reverify
};
struct convar_graphics
{
	inline static constexpr uintptr_t type_info = 0x0;
	inline static constexpr uintptr_t static_fields = 0xb8;
	inline static constexpr uintptr_t fov = 0x0;
};

namespace decryption {

inline uintptr_t base_networkable_0(uint64_t a1)
{
	std::uintptr_t rax = driver.read<std::uintptr_t>(a1 + 0x18);
	std::uint32_t* rdx = (std::uint32_t*)&rax;
	std::uint32_t r8d = 0x2;
	std::uint32_t eax, ecx;
	do {
		ecx = *(std::uint32_t*)(rdx);
		eax = *(std::uint32_t*)(rdx);
		rdx = (std::uint32_t*)((std::uint8_t*)rdx + 0x4);
		eax = ecx;
		ecx = ecx << 0x16;
		eax = eax >> 0xA;
		ecx = ecx | eax;
		ecx = ecx - 0x512FB7E6;
		ecx = ecx ^ 0x3C25B628;
		ecx = ecx + 0x606330A1;
		*((std::uint32_t*)rdx - 1) = ecx;
		--r8d;
	} while (r8d);
	return il2cpp_get_handle(rax);
}

inline uintptr_t base_networkable_1(uint64_t a1)
{
	std::uintptr_t rax = driver.read<std::uintptr_t>(a1 + 0x18);
	std::uint32_t* rdx = (std::uint32_t*)&rax;
	std::uint32_t r8d = 0x2;
	std::uint32_t eax, ecx;
	do {
		ecx = *(std::uint32_t*)(rdx);
		eax = *(std::uint32_t*)(rdx);
		rdx = (std::uint32_t*)((std::uint8_t*)rdx + 0x4);
		eax = ecx;
		ecx = ecx << 0x12;
		eax = eax >> 0xE;
		ecx = ecx | eax;
		ecx = ecx ^ 0xE54E9BFF;
		eax = ecx;
		ecx = ecx << 0x8;
		eax = eax >> 0x18;
		ecx = ecx | eax;
		ecx = ecx ^ 0xCECB4770;
		*((std::uint32_t*)rdx - 1) = ecx;
		--r8d;
	} while (r8d);
	return il2cpp_get_handle(rax);
}

} // namespace decryption


// ===========================================================================
// RAW CLASS DUMPS
// Everything below is emitted as C++ comments.  Use it to hand-map field
// offsets when a Rust patch renames or obfuscates things.
// ===========================================================================

// raw class: BasePlayer (label=BasePlayer klass=000001BC00C976C0 instance_fields=181)
//   %225ccb6046b7b746f7ce2645b4d9eca0b224b1cb @ 0x2C0  (PhoneController)
//   %6a208e6b431962ce9243d4a33f93b095e349d664 @ 0x2C8  (PlayerModifiers)
//   %0e514b93ae4454e49f09aa4e59726bd60c512899 @ 0x2D0  (WaterBody)
//   %d9df5b7631ca24181022c33c19013c9a81ea08fd @ 0x2D8  (System.Action)
//   %eb1eb78eb72ba738822b5202ce94ff2e225cdf4f @ 0x2E0  (System.Action<BasePlayer>)
//   %19710b1cd85883d0f3f9d19a80fc03d24be0ac45 @ 0x2E8  (BaseEntity)
//   %72bac4b4b7469a0ab5914c43b6b99388ee1fefee @ 0x2F0  (%3acf437cb2eba8f53ca24ed2aff82f67cb1f05bc<PlayerInventory>)
//   %f8e5cd966163dc46ce26806ad988eb9d77bc4eea @ 0x2F8  (UnityEngine.Collider)
//   %857e95644304313062d5fcb1b0849f7fd57b967c @ 0x300  (GestureConfig)
//   %bfc9e01ebfc6965712624c9d55c852f8fa86bcb8 @ 0x308  (System.Action<BasePlayer>)
//   %43ac4a1904bcb514824bca49d49a6619de6d8e82 @ 0x310  (%73a2ff516729fc8e7ce24e5231504821504fde50)
//   %6c903bc6529212b38d2738515a563398fec10af8 @ 0x318  (System.Action)
//   %447e273cfe31c69e9ceb0e634f0d9fdc0f3b8b54 @ 0x320  (System.Action)
//   %74a38dd4ddb2ede1855310890cd6f9499423d662 @ 0x328  (System.String)
//   %20910244d4797e3dc007ea9c9f7aac003486e2f0 @ 0x330  (%2983eedcba56e2affdec0d110c91931073a6f83f)
//   %e58987f637b226a09fdf800b1a54021022623252 @ 0x338  (System.Action)
//   %4edcdb849f6d8156884bd58a65e7526892332cc5 @ 0x340  (System.Action)
//   %f3127e425ed65ca9ba517d13ef2495b59d2c6230 @ 0x348  (System.Int32)
//   %104ed17aa5da402cf67e84126240d748e03f497f @ 0x350  (System.Int64)
//   %34b0475e196676410b2029f1d2cdd828434590c3 @ 0x358  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %526f5741c63edd2890f01e9b83e4ae7e62be37c7 @ 0x35C  (BasePlayer.CameraMode)
//   %4c6b0bdd672d4a7fdbdabe600b5e60e3a45ec6a5 @ 0x360  (BasePlayer.CameraMode)
//   %69d22df5b3c36cb2bc947ef8a5ba79de60ae70f2 @ 0x364  (UnityEngine.Vector3)
//   %3b3acfe0e71c2b06c73966c181368f3a405c0eb7 @ 0x370  (UnityEngine.Vector3)
//   %c88a5e5b365bc84b9645b821d240b05cf25f39ff @ 0x380  (System.Action<BasePlayer>)
//   %3908cc2e2a662784b9de6ce7d2112713f1cf4480 @ 0x388  (System.Boolean)
//   %e27c18eece41e3427474c1ee6b12dfaa7cc10769 @ 0x389  (System.Boolean)
//   %af64dbf31cac9bac5cd57f6b61bda60fc3cc04d7 @ 0x390  (BaseEntity)
//   %54586a3dfd0872a3ad08de4019786260152bc232 @ 0x398  (System.Action)
//   %9d4156da2dfcc62f76102b768e9693518907b5eb @ 0x3A0  (BaseEntity)
//   %99c484455deaff7b6e177b6fc1209080ee1c40d3 @ 0x3A8  (System.Collections.Generic.Queue<System.String>)
//   %9b733c705ba9a0e932232587b5f1b0ea87a293ba @ 0x3B0  (%a7dfe23573216c1b8747116ce98a310705957d60<BaseMission.%66b6333d882ebf0acb475e2bd631906611b5f4ab>)
//   %6ff90fde11ebdd4431c9c912301271ab183b9937 @ 0x3B8  (System.Int32)
//   %9e5cbcbc49dde39cf656eca3f03992cfac1f9f3b @ 0x3BC  (System.Int32)
//   %97b25f566a99093111c491839a9b753bc979ac6f @ 0x3C0  (System.Int32)
//   %f288fc3d74840787d977106c52e73b53dcb8901d @ 0x3C4  (System.Int32)
//   %f2a7d26d4a1a03faf6b7fddd043e1b14f5ea8195 @ 0x3C8  (%67d634f6be42874742008e503701166635022425)
//   %09f23d8f41d97f0b081f25ae2d97770b18bb0b07 @ 0x3D0  (System.UInt32)
//   %61eefc783a5720742e1ef650899748fefd7206e4 @ 0x3D4  (System.Single)
//   %b012a24fdc78a9179d17c0f80a5a8440a5d65f1c @ 0x3D8  (ProtectionProperties)
//   %50a0a4b7ddfd853fc43dc4884f94416ee806e364 @ 0x3E0  (UnityEngine.Collider)
//   %e88c87909ffd4ee4419a43b26beaa860a5755a55 @ 0x3E8  (%3acf437cb2eba8f53ca24ed2aff82f67cb1f05bc<PlayerEyes>)
//   %05e319642231d6c04d66b65985141f6419f7afe6 @ 0x3F0  (HeldEntity)
//   %a8b5073622ade275c03ef5209cc9d31993547895 @ 0x3F8  (UnityEngine.Vector3)
//   %7d4957854ee1ef8d678410ba1fc11021fe64b453 @ 0x404  (System.Single)
//   %7ddfb04d9dc8f5e2e3f442b5978f7e13786a0da2 @ 0x408  (System.Boolean)
//   %8b845dafc27bd2ecc942675acbc3984b644474a3 @ 0x409  (System.Boolean)
//   %540485b414e53b71c147e9ef82db4b868bf144e6 @ 0x40A  (System.Boolean)
//   %cc83965995578e55683471e80470f46d0f46eb48 @ 0x40B  (System.Boolean)
//   %1e236e85b8669993f06103075c92256bcf77bc15 @ 0x40C  (System.Boolean)
//   %cd204da4a95cc94f98996c4b9e23307e930faf42 @ 0x40D  (System.Boolean)
//   %8e1b52b0abd58c9f753bbd658d208ff2f104c48f @ 0x410  (System.UInt32)
//   %3d0ac50c3a8787fbaba353fd372ffdcf8e656731 @ 0x414  (System.Boolean)
//   %b5ca386e7c68b666f09bfa2730c8a8d7c7018f5a @ 0x415  (System.Boolean)
//   GestureViewModel                         @ 0x418  (ViewModel)
//   %30f826af23de57fb57c461defed6a5363f52ca68 @ 0x420  (%6962abfa9ad86be5d5b60038925fb6da2b447b3c)
//   %1f1d82115678006109f03b3768f1b09dd01dc991 @ 0x428  (System.Single)
//   %2ca491d502ee586c647e7cb003cac26311d86957 @ 0x42C  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %9316466095390bb2ba01b350b1e2d76d15b6201b @ 0x430  (%86139426fbc49b13d9ed7b5c1271168be6670fa4)
//   %1f67128353a7d319e0868f93c4ff42a2da776fd8 @ 0x434  (System.Single)
//   %8f730ab734852a2ebce9a3efa990b12bb7609759 @ 0x438  (UnityEngine.Vector3)
//   %ce00d8055f76b606576849ac5fc9987e7f3da984 @ 0x448  (System.Double)
//   %58a757bc4f5458943e2a6f60a01ae0e8783aa3f8 @ 0x450  (System.Single)
//   %afa62f16b72c0b8af4b468723245ccc5020a96b4 @ 0x454  (System.Single)
//   %c60f474e0b7eebf3d64cd07f0216085fb28b6da2 @ 0x458  (System.Action)
//   %37a387299cbef4208c788e0e0a5f685dd575a55e @ 0x460  (System.Int32)
//   %98d1fab22729a5f967e531d3d630305e17be50ef @ 0x464  (System.Int32)
//   %f9f1a4fe9e8e9ed8c52710d74d6caaf098c37a11 @ 0x468  (UnityEngine.Vector3)
//   %b7c8500f30642b0f825ffb1e065a6830605686a9 @ 0x478  (UnityEngine.Rigidbody)
//   %16a57c54b5e6cf3d1a0cb1aac83a10f115569846 @ 0x480  (System.Diagnostics.Stopwatch)
//   %09c87fa53b5662713f69b6b35d0a2861c4c0ffda @ 0x488  (System.Boolean)
//   %efbed46efca45ea60e2ce8c3fd171f5757009953 @ 0x490  (%b05837bf129cd4260975fabd3fa5ddae6563969f)
//   %db3fbed9c1d76c9d72209398ee0f7f7ec070b9f5 @ 0x498  (System.Action)
//   %80a497b91a97eb6dd2b02eae3a69269a1486ee1c @ 0x4A0  (%dcabb62517d1ead67908f3b0466c78b2b63950e1)
//   %f7b8aec1dc9bf3b69d5be1be57966951ef10dda1 @ 0x4A8  (System.Action<BasePlayer>)
//   %504ad8bf91ebeac38915c740561a000250709d70 @ 0x4B0  (UnityEngine.Vector3)
//   %c7efc395147c1b8e7d644ec8ce7072864ebd3fba @ 0x4BC  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %1b83922322b2c72f4b90f8b1312bf555bc3ba967 @ 0x4C0  (System.Boolean)
//   %71c163066311d575364273dc9c38235cfa9573f1 @ 0x4C4  (%0d293ed25c0aac1226694e96e3766c7a4e601aec)
//   %c3e75de5e456fcb3fef1e5b45fff2a4a4d4770a6 @ 0x4C8  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %51ed7b7094eb398f5789d08078de4ac5cf358cae @ 0x4D0  (System.Action<BasePlayer>)
//   %eb4dc3b9f28292849be8099a9ed9d93ff778e8db @ 0x4D8  (UnityEngine.Collider)
//   %92c5fb788f03046540c5efa26d1a01e82505fa86 @ 0x4E0  (System.Action<BasePlayer>)
//   %dc116a854eef9cead5bc782e8fcb2226cfc2853a @ 0x4E8  (System.Single)
//   %35a14b0b43f798524aa87a25865ef4b7f75c4349 @ 0x4EC  (System.Int32)
//   %6bbba32029b796071e9905387162d868b12e9b3a @ 0x4F0  (UnityEngine.GameObject)
//   %9af51e0b43e49c8f5f7c0e9626efb2b62395c476 @ 0x4F8  (System.Collections.Generic.Dictionary<System.String,%83b4e6d678cd9a4c3ec4878b701120be14f6f33c>)
//   %925d0cd75de4485dffac8982fd1481f7726463b7 @ 0x500  (PlayerModel)
//   %2b755bb11302595a05a3706abc4bdf12e3bba30f @ 0x508  (System.UInt32[])
//   %7fc0ca3222406375883739dec588f8ca6204647d @ 0x510  (PlayerMetabolism)
//   %70791f7d40aa4c53db87e26000dac5f13d4d0cd9 @ 0x518  (PlayerInput)
//   %ba1626ebe87d18d93deb7ab4fd0f1348fa083a7f @ 0x520  (System.Action<BasePlayer>)
//   %9c56dfab905f8d0ed79527e9a467298cfe5677fe @ 0x528  (%084d4958e2d9a536179dae305b1bec5b88986975)
//   %26540c91d32ad1decc90c38e8ca1306ea4fa051d @ 0x530  (System.Single)
//   currentTeam                              @ 0x538  (System.UInt64)
//   %6c0725c7b16c874cc4c8a2ef74407e2d6a375be6 @ 0x540  (System.Collections.Generic.List<%2983eedcba56e2affdec0d110c91931073a6f83f>)
//   %53ebb9ee826866638b6eee94bf2d2aae17887704 @ 0x548  (ProtectionProperties)
//   %3fe8522576a78b7a1308f78cf4c622acdebf6df2 @ 0x550  (System.Single)
//   %253e038dc1418fb8eab1a4b01e65f339cdf5e207 @ 0x558  (System.UInt64)
//   %3d2857b9e56d3de7c9f2c0232dbd121ed5a94f7a @ 0x560  (System.Int32)
//   %31902f866a8a35e9c3eeacd36897e018a9c7b361 @ 0x568  (%2cad33a9772366eb0a6a4a01a4bc6b2f8abeafd6<%1d6a0aa2fe65126c6a31d6af1a48dc120315dc35>)
//   %959f1bfd649846616d0529fc3cf946933ee303a7 @ 0x578  (System.Boolean)
//   %fc4d1e9e08af9f3092bac67c2855f3dd016ce021 @ 0x57C  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %98d3231d59278cc04413e23cd39100500ce2ed3c @ 0x580  (PlayerVoiceRecorder)
//   %9333ea180a3794ef216b1b3e587528437a973c04 @ 0x588  (BasePlayer)
//   %a84c9d8dac797c2de8f66895a412f937ea92d388 @ 0x590  (System.Boolean)
//   %ee0b78d06a6f926684e28c812a173962ff204380 @ 0x598  (%3acf437cb2eba8f53ca24ed2aff82f67cb1f05bc<UnityEngine.CapsuleCollider>)
//   %e2423e67bc476b9246398b8af45f38ce4b0caeb5 @ 0x5A0  (System.Single)
//   %cf32365c1ea4283a0fc8650b81b0e9051c852743 @ 0x5A8  (System.Action<BasePlayer>)
//   %ba531fe5be8484acb753b4614f4d8dc5282ca98d @ 0x5B0  (System.Int32)
//   %972e9ac32e21e13bbf8864bceabb463cbf9d3d7e @ 0x5B4  (System.Single)
//   %e867322a3b8ecc27661054b1da2729417ef3d004 @ 0x5B8  (System.Action<BasePlayer>)
//   %2c42e8138704a2a97e0a377202d6ad642c17dcb6 @ 0x5C0  (%91f5897cc0e90474f41909c855d8a1c8b087e582)
//   %1eb275651b1f03174db5a3fbce55990a9cb184a1 @ 0x5D0  (%67d634f6be42874742008e503701166635022425)
//   %716feffdc7fc191c5369242abe3dc12331b7cb10 @ 0x5D8  (System.Single)
//   %5e4feb736a8552123f3f5c54fc84c0af95a070d3 @ 0x5DC  (System.Boolean)
//   PetEntity                                @ 0x5E0  (BaseEntity)
//   %9f09a316d4c4e8ea3f2eae89964c7bda8fa227c3 @ 0x5E8  (System.Single)
//   %c00255da386dbd33cc787111411d99bf465a1173 @ 0x5EC  (System.UInt32)
//   %37111beffde18dce4060ec88de9737e2adad45de @ 0x5F0  (%67d634f6be42874742008e503701166635022425)
//   %7669184911284e936b1f8e39ff41ffb3411bfaf8 @ 0x5F8  (System.UInt32[])
//   %0427227683e2506fa62d74c74252a5c93452a617 @ 0x600  (System.Boolean)
//   %10373bb47c197fa292bf30d22a45557dd6358076 @ 0x604  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %1810b25f21bc8bbe8b198dcafd66fc6c85e4466a @ 0x608  (System.Single)
//   %772f98384365a50a0da6ab0879c88ebcdbc07c9c @ 0x610  (System.String)
//   %e76789df1785d37e580f65b26c9cc68701aef5bb @ 0x618  (System.Boolean)
//   %f1687302afd05f2439ab47582e1555243d15b11f @ 0x61C  (UnityEngine.Vector3)
//   %94e33cb2c7cc1c867052ccc894d29857b24d2df7 @ 0x628  (System.Single)
//   %88122ea7b03610fda49eabe0ba592bfae4e50a98 @ 0x630  (PlayerVoiceSpeaker)
//   %3b77bb49ed22f778436fb488b09d756aaabf42af @ 0x638  (System.Boolean)
//   %df8cb660204aefec99a58a8eef052961b379d9df @ 0x63C  (UnityEngine.Vector3)
//   %5f133a387ed7080a375a2a46185d79858d0b76f3 @ 0x648  (%0d293ed25c0aac1226694e96e3766c7a4e601aec)
//   %ff5b3e1ded0e19eed474bf3cd93e41165561b0ef @ 0x64C  (System.Int32)
//   %24d73769366313bb485f9183a1b578cc9b820294 @ 0x650  (%67d634f6be42874742008e503701166635022425)
//   %17b7d428f81fd67a544cd4e5476fe2d6e5ac72b1 @ 0x658  (GestureConfig)
//   %705dc8406d6eeb485b9215d1e7d55fb093f94b05 @ 0x660  (UnityEngine.Vector3)
//   %798ec6e0ca242b4a9115e8b0f660e8137ca52810 @ 0x66C  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %dd31c2f7145cf65d15a1673e0445a9a472fac467 @ 0x670  (System.Single)
//   %e1cd9df06f4ffaa6f514a155092f40dbaa4a84f8 @ 0x674  (System.Single)
//   %e0e09a0b185ca11b129bf84624ecee36888a4b94 @ 0x678  (%2cad33a9772366eb0a6a4a01a4bc6b2f8abeafd6<System.Single>)
//   %d44f43806b39bc798d6b37c388bc69888dc963c8 @ 0x680  (System.Action<BasePlayer>)
//   %25e7a87ff32163dc4325b7f2c9bfbcb98b53d2bb @ 0x688  (System.Action)
//   %3997ab1f46a0c696e53157f7f48007fa40a371dc @ 0x690  (System.Int32)
//   %531f30866de076f768ec18691aa19be34d8c42bb @ 0x694  (System.Single)
//   %a93128f305da2d8b7e84b37cf06b543e36726252 @ 0x698  (System.Single)
//   %f447c5dfd87af40a8d36a05ffa80fac63c07a4e5 @ 0x69C  (System.Single)
//   %aef385d4aeff033337d80ffd2b84dfe606208e53 @ 0x6A0  (System.Boolean)
//   fallDamageEffect                         @ 0x6A8  (GameObjectRef)
//   drownEffect                              @ 0x6B0  (GameObjectRef)
//   playerFlags                              @ 0x6B8  (BasePlayer.PlayerFlags)
//   %dca6eb11b3c52b3c03f9bd17785dea4046e0ab4f @ 0x6C0  (System.Action)
//   %c61aeae470e9766b6387d7c1a2354a2ed026bd45 @ 0x6C8  (System.Collections.Generic.Dictionary<System.ValueTuple<%67d634f6be42874742008e503701166635022425,System.UInt32>,System.Boolean>)
//   %a498e164f2edfcdfca01268c4918e2909da522ba @ 0x6D0  (System.Action<BasePlayer>)
//   %6b35ff06dfe6bf143ebee72f5418654d7b0cf5eb @ 0x6D8  (System.Action<BasePlayer>)
//   %33951e8b14e13e35786849a8cf56d7711ad67fc2 @ 0x6E0  (System.String)
//   %0d56e2a1675eb567b191e1efa0e5b47e814a8a3d @ 0x6E8  (System.Action)
//   %67f0b5150979820fa98b486d07e476a9b06a8864 @ 0x6F0  (PlayerBlueprints)
//   %42b31c0d1cc10c3be0815fec2a3402a578a8df3a @ 0x6F8  (System.Collections.Generic.List<%2983eedcba56e2affdec0d110c91931073a6f83f>)
//   %2566f5d0ca35ee4af47db134ca8be7bc803f1a97 @ 0x700  (%2cad33a9772366eb0a6a4a01a4bc6b2f8abeafd6<System.UInt64>)
//   %b509efaee9d7d96eac6a083506ba62784c8eba87 @ 0x710  (System.Action<BasePlayer>)
//   %0e872df21163fd199db7d2cc44ea3c92eec8e6d0 @ 0x718  (System.Int32)
//   %fa720ac72393163d5d6f4862476c505b0de14294 @ 0x71C  (System.Int32)
//   %a66c7ff8907e95a17b66a283088912b7a042f173 @ 0x720  (System.Action<BasePlayer>)
//   %0693cc17b10e18d2b4c948a1189ad864b37fcf29 @ 0x728  (BaseCollision)
//   %3c48af6fdb212800acf4aeb51245ed69c99659ba @ 0x730  (BasePlayer.CapsuleColliderInfo)
//   %f00290abe07eb259285a293f97c54189efdb2792 @ 0x744  (BasePlayer.CapsuleColliderInfo)
//   %6e1dc7b84bcc1cdea0bf0f6da784b09390a59c94 @ 0x758  (BasePlayer.CapsuleColliderInfo)
//   %59b5e34e93054e07a3b87ef9590d8409a308fad3 @ 0x76C  (BasePlayer.CapsuleColliderInfo)
//   %cb611bdc1236c86b4cfb50111779efe11232f7ff @ 0x780  (%e7cde6d688cc4fa19c20aed9beb40ce49b67cb92<System.UInt64>)
//   %cd977ecf0a9fa058e9e07a9ed4894f83e704dedb @ 0x788  (BaseMovement)
//   %fa74796608f644c41a470f100c9caabebb6a7880 @ 0x790  (System.Single)
//   %db2cdf898280e9662191588348f63761e2ee5fde @ 0x794  (System.Single)
//   weaponMoveSpeedScale                     @ 0x798  (System.Single)
//   clothingBlocksAiming                     @ 0x79C  (System.Boolean)
//   clothingMoveSpeedReduction               @ 0x7A0  (System.Single)
//   clothingWaterSpeedBonus                  @ 0x7A4  (System.Single)
//   clothingAccuracyBonus                    @ 0x7A8  (System.Single)
//   equippingBlocked                         @ 0x7AC  (System.Boolean)
//   eggVision                                @ 0x7B0  (System.Single)
//   %1fda30fc0046b8be0c22dd6dffb87a37bbaaac7d @ 0x7B8  (%d6bd762cf29423b6c08390e3b7a72441d5df5696)
//   designingAIEntity                        @ 0x7C0  (BaseEntity)

// raw class: BaseCombatEntity (label=BaseCombatEntity klass=000001BC00B526B0 instance_fields=23)
//   %dd8e8baa7ffc70dc7e92c5feb59c5b582920896d @ 0x1F0  (System.Action)
//   %2a01434996948e40464dcf83bc1e734a90f335aa @ 0x1F8  (System.Action<BasePlayer>)
//   spawnDeployableCorpseOnDeath             @ 0x200  (System.Boolean)
//   deployableCorpsePrefab                   @ 0x208  (GameObjectRef)
//   %cab5a951374f4932e71f07b21bf3d8fc6eab977c @ 0x210  (System.ValueTuple<%7f632395dd52341c069ed0683b05893b38f6577d.Phrase,%7f632395dd52341c069ed0683b05893b38f6577d.Phrase>)
//   skeletonProperties                       @ 0x220  (SkeletonProperties)
//   baseProtection                           @ 0x228  (ProtectionProperties)
//   startHealth                              @ 0x230  (System.Single)
//   pickup                                   @ 0x238  (BaseCombatEntity.Pickup)
//   repair                                   @ 0x260  (BaseCombatEntity.Repair)
//   ShowHealthInfo                           @ 0x290  (System.Boolean)
//   showHealthInfoThreshold                  @ 0x294  (BaseCombatEntity.ShowHealthThreshold)
//   lifestate                                @ 0x298  (BaseCombatEntity.LifeState)
//   sendsHitNotification                     @ 0x29C  (System.Boolean)
//   sendsMeleeHitNotification                @ 0x29D  (System.Boolean)
//   markAttackerHostile                      @ 0x29E  (System.Boolean)
//   %32f736f0fa89188f80288ae4bccac66ced0b413f @ 0x2A0  (System.Single)
//   %e28fc72bef2ca203f1fbda251be13cc7c4acbb7b @ 0x2A4  (System.Single)
//   %b149f3d4fa9ecbba4f49d4bd427155185999bf2c @ 0x2A8  (System.Single)
//   faction                                  @ 0x2AC  (BaseCombatEntity.Faction)
//   %b0a6186ff9c6945db37ce99c2ab335e9da6681bb @ 0x2B0  (System.Single)
//   %7cc37a5fb3d53b0d66c0e3241a4496cf01ee6361 @ 0x2B4  (System.Single)
//   %15c266ff1d31a93efb0414a9693b96803baad98b @ 0x2B8  (System.Int32)

// raw class: BaseEntity (label=BaseEntity klass=000001BC00B572E0 instance_fields=43)
//   %cd5180a811d445f87e2b48e87f906c29ee1202c3 @ 0x090  (ItemSkin)
//   %3cbeeeafb7018093fbbe04a1db1eb146f459f0a3 @ 0x098  (BaseEntity)
//   %1bcd940de9d46717d132fe32e5e11bc7e1e83605 @ 0x0A0  (System.Collections.Generic.List<TriggerBase>)
//   %cd40d682d90e11846126135029a99c67843820be @ 0x0A8  (System.Collections.Generic.List<%cf601296148cd65fc0f1421378c029e9e91e816c>)
//   %1d259e313b12c1c273a649d55acfeb531acf22cd @ 0x0B0  (System.Single)
//   %95b2643c784d4f41b4673ad208dfca037075223e @ 0x0B8  (%91f5897cc0e90474f41909c855d8a1c8b087e582[])
//   %e7013b11a6ea4cfecc0c3369e6f8f1ea0e1aa89e @ 0x0C0  (System.UInt32)
//   %24f94a2cbbf0ced73af691f5f6964c1be11bc909 @ 0x0C8  (System.Action)
//   %4f06889a01f5bfa225572515b5bea99730fb8406 @ 0x0D0  (System.Boolean)
//   %ff8a818fbfb4013e3529a62122a9398ee0794016 @ 0x0D8  (System.Collections.Generic.HashSet<System.Int32>)
//   %1068141e8613a5315b1a40e54e6f2a12be76f15e @ 0x0E0  (System.Nullable<System.Boolean>)
//   %9265c04ce2a764326c5d16720f15846205a6d120 @ 0x0E8  (System.String)
//   %4df881f5f60d05b53ffa71fbf3b91c7e1974ef86 @ 0x0F0  (BuildingPrivlidge)
//   %eb77c7cba60d9d40c7603ba3bae278143007cf8b @ 0x0F8  (System.Single)
//   %56b393b75a624dd8bab27ef5a7ee0616df20b48d @ 0x100  (System.Collections.Generic.List<BaseEntity.%503dc70197674d8dee98722a29f4752ddee82467>)
//   %36618ab5eca39b5528bae74dbdfc2be70044713b @ 0x108  (UnityEngine.Vector3)
//   %fa4702c6b0784bbb6ecc2077e80f99f282e7a98f @ 0x118  (System.Action)
//   %f5655af55b6cce4ad1dce96832ffc7926b1223be @ 0x120  (Ragdoll)
//   %e30fa3455c84b9cc88854d0bed8709aacf5833d8 @ 0x128  (System.Action)
//   %1b4a5462c522b2eaf01b141339a3bb562b8ea3aa @ 0x130  (System.Collections.Generic.List<%266905e6cb63bb51b2a7a071253ca891e90fcb6c>)
//   %1e6f7c304e32a847dce67c875d55f7a146658a8b @ 0x138  (System.Collections.Generic.List<EntityComponentBase>)
//   %bcf2c66386cfc5c80b271ec5fad9b64cba8ec043 @ 0x140  (System.Boolean)
//   %f7ef04abdc83a3caf646eb6531175c6c7b5a2a01 @ 0x148  (BaseEntity)
//   %ce763325f8d1936fd011f8170d8818b8f54e8129 @ 0x150  (System.Boolean)
//   %0cf8885c4272b0d32e0721c572b41d3abde92ef3 @ 0x151  (System.Boolean)
//   %f08ae563ea0d820d3cb97343152bc1e9da68878a @ 0x152  (System.Boolean)
//   %1e507a4cbd2116bd3e9aa0ee40468153255dbc5e @ 0x158  (%5a90aef0605446a3dc3da2744e4794734f98e094)
//   %5b98d2e54213e92d92138e6930e9721f25a204ca @ 0x178  (System.Single)
//   bounds                                   @ 0x17C  (UnityEngine.Bounds)
//   impactEffect                             @ 0x198  (GameObjectRef)
//   enableSaving                             @ 0x1A0  (System.Boolean)
//   syncPosition                             @ 0x1A1  (System.Boolean)
//   model                                    @ 0x1A8  (Model)
//   flags                                    @ 0x1B0  (BaseEntity.Flags)
//   %13a55e84c5a9e330f320eed296544578aa1902a2 @ 0x1B4  (System.UInt32)
//   %d75472d42b904cfcd52c747c6566bebec0407e50 @ 0x1B8  (System.UInt64)
//   %6c5d3f9ef0b95c8b25b1dab3328616639be54d7a @ 0x1C0  (System.UInt64)
//   %00948ea8f3e6e63f4a6da4bc206aebf961587d80 @ 0x1C8  (%459e39893bc6c07a944a2b191fd10000a2f5a6e5)
//   HasBrain                                 @ 0x1D0  (System.Boolean)
//   %4c2adc13728a5add5c3ef4536f470174535cb694 @ 0x1D4  (System.Single)
//   %0f2e1f9358cd6aa5761680dbe2faeebc502cafc1 @ 0x1D8  (System.Boolean)
//   %daa1852e882bed5e86bf4bf16c6af138be467c83 @ 0x1E0  (System.Action)
//   %16c27d763fc274001c87a20ed92289c9df3f4e72 @ 0x1E8  (System.UInt64)

// raw class: PlayerModel (label=PlayerModel klass=000001BC03CBA0B0 instance_fields=173)
//   %589157f868525a507433dc7261f667fc1bc1da8f @ 0x020  (System.Single)
//   %42c4ca1310c83641309fc92ea9c14a77d9f789a2 @ 0x024  (System.Single)
//   %2d6741232e8a0fd5337d0f4867e25f5b350ac3c2 @ 0x028  (UnityEngine.Vector3)
//   %1b802c934d0a9da179a807aacf26e485d62d8fbd @ 0x034  (System.Boolean)
//   %9c932d20ee1146974c5af6446cc1ba6779b65cf5 @ 0x038  (System.Single)
//   %40868ab313605cd492c5ed3ba7a222509bc89747 @ 0x03C  (System.Single)
//   %5f9220c6a18ae4547dc0c128c225d8630d58f563 @ 0x040  (System.Single)
//   %29d958239cb65ba2e94ce980d7b1bb141175ea9e @ 0x044  (System.Single)
//   %1cad0e672f4191ddb3b543e9974de66990bca8b5 @ 0x048  (System.Single)
//   %9fb60ad2a99b571e837e63d32e60f7031b396cbd @ 0x04C  (System.Single)
//   %90d3ab8a05e5b6b81060b97406e3bf45681fee69 @ 0x050  (System.Single)
//   %16937ec2945015a9ab5d747f4bde08e26062e607 @ 0x054  (System.Single)
//   %20dec893c174955bfb6ae781df5cbaa838413f59 @ 0x058  (UnityEngine.Vector3)
//   %8fc6956b8a018f382d5dfae131120eac1fdb8062 @ 0x064  (UnityEngine.Vector3)
//   %0c7917e48cebbc96422a939ad9d57b59e8db8809 @ 0x070  (UnityEngine.Vector3)
//   %3568b0d73266c81e15a8789bc68ddd721126a51c @ 0x07C  (UnityEngine.Vector3)
//   %1d6d0242c4d7aa3adf6ea39f93873c347d57f0d2 @ 0x088  (System.Single)
//   %527007ae95e7794dc802152858c217c40b150ed1 @ 0x08C  (System.Single)
//   %c6abf9016ff9b3b6b5951ef4477e1ba6b7a7c2bb @ 0x090  (System.Boolean)
//   Shoulders                                @ 0x098  (UnityEngine.Transform[])
//   AdditionalSpineBones                     @ 0x0A0  (UnityEngine.Transform[])
//   %9848e8babb1050b818cf048f9ee2d48cebde29cc @ 0x0A8  (GestureConfig)
//   %c08085fa0664bd277c193abc9e4928770d01f1de @ 0x0B0  (PlayerNameTag)
//   %0f55da1cfa95e8e14e6bf9908830974c2d7abd6f @ 0x0B8  (System.Collections.Generic.List<WearableFadeToggle>)
//   %7506f780a5dfb47021949e84d6f3c4aaca67fa01 @ 0x0C0  (System.Single)
//   %407e4582c554d014a075a059ae37af01c27aa37d @ 0x0C4  (System.Nullable<System.Boolean>)
//   %0be0e481f927a8a065605cd812bad2293cfe7dc3 @ 0x0C8  (System.Single)
//   %3df068637e4bb452506f169795376fdbd20d38ed @ 0x0CC  (%0d293ed25c0aac1226694e96e3766c7a4e601aec)
//   collision                                @ 0x0D0  (UnityEngine.BoxCollider)
//   censorshipCube                           @ 0x0D8  (UnityEngine.GameObject)
//   censorshipCubeBreasts                    @ 0x0E0  (UnityEngine.GameObject)
//   jawBone                                  @ 0x0E8  (UnityEngine.GameObject)
//   neckBone                                 @ 0x0F0  (UnityEngine.GameObject)
//   headBone                                 @ 0x0F8  (UnityEngine.GameObject)
//   leftEye                                  @ 0x100  (UnityEngine.GameObject)
//   rightEye                                 @ 0x108  (UnityEngine.GameObject)
//   eyeController                            @ 0x110  (EyeController)
//   blinkController                          @ 0x118  (EyeBlink)
//   SpineBones                               @ 0x120  (UnityEngine.Transform[])
//   leftFootBone                             @ 0x128  (UnityEngine.Transform)
//   rightFootBone                            @ 0x130  (UnityEngine.Transform)
//   leftHandPropBone                         @ 0x138  (UnityEngine.Transform)
//   rightHandPropBone                        @ 0x140  (UnityEngine.Transform)
//   rightHandTarget                          @ 0x148  (UnityEngine.Vector3)
//   leftClavicleBone                         @ 0x158  (UnityEngine.Transform)
//   isPreview                                @ 0x160  (System.Boolean)
//   leftHandTargetPosition                   @ 0x164  (UnityEngine.Vector3)
//   leftHandTargetRotation                   @ 0x170  (UnityEngine.Quaternion)
//   rightHandTargetPosition                  @ 0x180  (UnityEngine.Vector3)
//   rightHandTargetRotation                  @ 0x18C  (UnityEngine.Quaternion)
//   leftUlnaTwistBone                        @ 0x1A0  (UnityEngine.Transform)
//   rightUlnaTwistBone                       @ 0x1A8  (UnityEngine.Transform)
//   leftHandTwistRelaxWeight                 @ 0x1B0  (System.Single)
//   rightHandTwistRelaxWeight                @ 0x1B4  (System.Single)
//   steeringTargetDegrees                    @ 0x1B8  (System.Single)
//   playerBoatSteeringTargetDegrees          @ 0x1BC  (System.Single)
//   rightFootTargetPosition                  @ 0x1C0  (UnityEngine.Vector3)
//   rightFootTargetRotation                  @ 0x1CC  (UnityEngine.Quaternion)
//   leftFootTargetPosition                   @ 0x1DC  (UnityEngine.Vector3)
//   leftFootTargetRotation                   @ 0x1E8  (UnityEngine.Quaternion)
//   legsAnimator                             @ 0x1F8  (FIMSpace.FProceduralAnimation.LegsAnimator)
//   upperBodyMask                            @ 0x200  (UnityEngine.AvatarMask)
//   fullMask                                 @ 0x208  (UnityEngine.AvatarMask)
//   CinematicAnimationController             @ 0x210  (UnityEngine.RuntimeAnimatorController)
//   DefaultAvatar                            @ 0x218  (UnityEngine.Avatar)
//   CinematicAvatar                          @ 0x220  (UnityEngine.Avatar)
//   DefaultHoldType                          @ 0x228  (UnityEngine.RuntimeAnimatorController)
//   SleepGesture                             @ 0x230  (UnityEngine.RuntimeAnimatorController)
//   CrawlToIncapacitatedGesture              @ 0x238  (UnityEngine.RuntimeAnimatorController)
//   CrawlToIncapacitatedGestureHandcuff      @ 0x240  (UnityEngine.RuntimeAnimatorController)
//   StandToIncapacitatedGesture              @ 0x248  (UnityEngine.RuntimeAnimatorController)
//   %34a83d4ab832f5394c93ce9a70ac91e35910c6bd @ 0x250  (%e7cde6d688cc4fa19c20aed9beb40ce49b67cb92<AnimationSubSystem>)
//   MaleSkin                                 @ 0x258  (SkinSetCollection)
//   FemaleSkin                               @ 0x260  (SkinSetCollection)
//   MannequinSkin                            @ 0x268  (SkinSetCollection)
//   subsurfaceProfile                        @ 0x270  (SubsurfaceProfile)
//   voiceVolume                              @ 0x278  (System.Single)
//   skinColor                                @ 0x27C  (System.Single)
//   skinNumber                               @ 0x280  (System.Single)
//   meshNumber                               @ 0x284  (System.Single)
//   meshSubNumber                            @ 0x288  (System.Single)
//   hairNumber                               @ 0x28C  (System.Single)
//   dyeNumber                                @ 0x290  (System.Single)
//   skinType                                 @ 0x294  (System.Int32)
//   mouthFlapPosRange                        @ 0x298  (System.Single)
//   mouthFlapRotRange                        @ 0x29C  (System.Single)
//   mouthSidePosRange                        @ 0x2A0  (System.Single)
//   mouthSideFrequency                       @ 0x2A4  (System.Single)
//   movementSounds                           @ 0x2A8  (MovementSounds)
//   showSash                                 @ 0x2B0  (System.Boolean)
//   tempPoseType                             @ 0x2B4  (System.Int32)
//   underwearSkin                            @ 0x2B8  (System.UInt32)
//   %d4d4f3b653142561c74b7ba2c60a7d94e3d5f461 @ 0x2BC  (System.Int32)
//   %3972aa6b74fd0d73eb810974f563e3944d3f0663 @ 0x2C0  (System.UInt64)
//   %4bafab1583066ab65253e503a0833d466e4ec112 @ 0x2C8  (UnityEngine.Quaternion)
//   %8679af378552a4ba2ac4eb69e141161bec9a4471 @ 0x2D8  (UnityEngine.Quaternion)
//   %e8d8d43120a9e8ced15dc179bab7130d92c90144 @ 0x2E8  (System.Boolean)
//   %4bf411c614c6e390202e1e238f9d4089ee8ca589 @ 0x2F0  (UnityEngine.RuntimeAnimatorController)
//   %e9839d2c7eee60bd9486cb6cbe3fcc9679a04a33 @ 0x2F8  (UnityEngine.Vector3)
//   %84e3e65f8dfa7157e3c24c2a4769ce8cb7ae77ba @ 0x304  (UnityEngine.Vector3)
//   %db23d500701187240f2b82a17510c22a3babc2b9 @ 0x310  (UnityEngine.Vector3)
//   %876a1a847b24bfccafe88b100a14222e16030fbd @ 0x31C  (UnityEngine.Vector3)
//   %4bbc8c24d51b2256576251820d19115973eeca91 @ 0x328  (UnityEngine.Quaternion)
//   %65135e8a9cfbcaadd4fe75d0dd801bbb44c4ead0 @ 0x338  (UnityEngine.Quaternion)
//   %dc33a43e0a0da4724e4d2aed246776bf07e0b4a5 @ 0x348  (System.Single)
//   %72cedba288ea4d16f90480b258c66d89e870a171 @ 0x34C  (System.Nullable<System.Single>)
//   %bb4867de7b633537439137b8330f86aa05f6c2dd @ 0x354  (System.Nullable<System.Single>)
//   %22f651f63e1e8d34c8b945e3acd87fab84fa23c9 @ 0x35C  (UnityEngine.Vector3)
//   %91562ca623ccbba9040bf4ef040cfa52d481f37c @ 0x368  (UnityEngine.Vector3)
//   %954ce4d1c8f528011a629564a0b882cd5a36d22d @ 0x374  (System.Boolean)
//   %1bc86edc1603dd743fcb4ad6ccf571f063346968 @ 0x375  (System.Boolean)
//   %b4be93a9fca5127f4da6cd9277012ed0fd6489cb @ 0x378  (System.UInt32)
//   %1485a194e8c983dae44cdabbb76da2847e701a7e @ 0x37C  (System.Boolean)
//   %524645771e303f6bbe1057e5c929ea5dac19f7bf @ 0x380  (SoundDefinition)
//   %9c14cbfcea3f48c4b907fa6302fdf10cc5d4f28d @ 0x388  (System.Boolean)
//   %29e02e2d36aabb9bbbe51f4bf52d4b228ca5bc70 @ 0x389  (System.Boolean)
//   %9fc3d19a3374feab02cabc4b4a99aaa3670787ea @ 0x390  (SoundDefinition)
//   %405ff15bfcfb29d4a42a846adb10248021b15b37 @ 0x398  (SkinnedMultiMesh)
//   %ffafe567d618085b174a8c59813ca634f7b403c1 @ 0x3A0  (System.Boolean)
//   %cbd46a6be167cb7826d59de5013c009cbe3047bf @ 0x3A8  (UnityEngine.RuntimeAnimatorController)
//   %76d5d79bff16c9e4edd5ec01c14b3884c8c7cde9 @ 0x3B0  (%0d293ed25c0aac1226694e96e3766c7a4e601aec)
//   %a0986c844b56cc17fba871e3e65936a8ee73dd56 @ 0x3B4  (System.Boolean)
//   %1ca9350596fcb77b31be109610a2bf0986c5b8b2 @ 0x3B8  (System.Collections.Generic.List<UnityEngine.SkinnedMeshRenderer>)
//   %b67150b98a1f4b08283cca3c241ef344fb2149f2 @ 0x3C0  (UnityEngine.RuntimeAnimatorController)
//   %6cc38cf2ee43119f698e621b9931f970daff2504 @ 0x3C8  (System.Nullable<%59d17a15c907cb07446855ab68a66f3d8379ebb3>[])
//   %243463bad8f1f4bfcef0f5b08ee79bedee5be90a @ 0x3D0  (UnityEngine.RuntimeAnimatorController)
//   %a43e01baad34cf39805031649717de8213983a07 @ 0x3D8  (UnityEngine.Playables.PlayableGraph)
//   %44ae0f4ce9485f3f7aa3167543ae48270514e8d9 @ 0x3E8  (System.Boolean)
//   %d53ef9ad7941646c5c5ba5a96cf1ca85094e42a5 @ 0x3F0  (UnityEngine.Animations.AnimationLayerMixerPlayable)
//   %935bea63c3392cd00741890087f6c4e8472acd73 @ 0x400  (UnityEngine.Animations.AnimationPlayableOutput)
//   %39b5a3e2cb70300a8ed8f8c02920a0373ff09112 @ 0x410  (UnityEngine.Animations.AnimatorControllerPlayable)
//   %dea2d00c826055983d774047601ec370b69e237f @ 0x420  (UnityEngine.Coroutine)
//   %eb4183ff1894606572655ca665ec4e05b2289fe9 @ 0x428  (UnityEngine.Animator)
//   %cc4557b52f45158388b8bb46be2da6c14b6d7899 @ 0x430  (UnityEngine.Animations.AnimationClipPlayable)
//   %2e46b20ad67344ef91743456dc02711afb0e11a2 @ 0x440  (HeldEntity)
//   %f0bcd03e8cce8c7ff4c23044f07c03bfeeb36241 @ 0x448  (System.Collections.Generic.List<BlendShapeController>)
//   %2945a764e49a8730eaeb9bafc7f750270e101a45 @ 0x450  (System.Single)
//   %a7d7115b6ee3d2dbd474ba1f5f192f7164e06305 @ 0x454  (System.Boolean)
//   %028deb168c6912f151da95534d1834624e1a0a1b @ 0x455  (System.Boolean)
//   %dbf6811fafc5724658dfbeedddaa698b90eeedca @ 0x458  (System.Int32)
//   %f8f1c7d52527786acd257f0eced4347a7fed5140 @ 0x45C  (System.Int32)
//   %93968d13fc8033fb0549dd1411d3c63929f9b80d @ 0x460  (ItemModWearable)
//   %b646ee6301a95166122d291c7db427ae91bb9853 @ 0x468  (System.Boolean)
//   %418cccbac531d8bc4080dc99079b355abfcd7613 @ 0x46C  (System.Single)
//   %45ebabf0ff1fe09710f867438407f04778a6ad03 @ 0x470  (System.Single)
//   %7e9adbde33c42defa74e223a2fea4763d39d1649 @ 0x474  (System.Boolean)
//   %6d3b9d11c5681a11462e18485ca69c5e77324c4f @ 0x478  (System.Int32)
//   %d801e681be4bb712cf2600ae137fc2985959eccd @ 0x47C  (System.Boolean)
//   %6c0690e562ff56c0cc051f24f4a41c97f73c518f @ 0x480  (System.Nullable<System.Single>)
//   %e09e66e80eba0d0b300f7df46eb61f17f5bedd83 @ 0x488  (UnityEngine.LODGroup)
//   %4d696cd96381aa67cc7f87c0fcffe9af45a51e9a @ 0x490  (System.Boolean)
//   %5f97068bdf0141d78b9ad811b0df1d7a0958a3b7 @ 0x491  (System.Boolean)
//   %97d07f141c45b70b36ab1a9e63bb94168b527e11 @ 0x492  (System.Boolean)
//   %318173016ab3925a0f1a530cb1df735c2f5c0b33 @ 0x494  (System.Int32)
//   %4402a45107c0bf35a4882fb5e0af3043341d2622 @ 0x498  (UnityEngine.Vector3)
//   %e5395247a735324c31726b14d5aba8acea969ab7 @ 0x4A4  (UnityEngine.Quaternion)
//   %aa1bdd8cf5230c7ded042ff08e41bf3a5aecac73 @ 0x4B4  (HeldEntity.HoldInfo)
//   %00a5a53c8303274b2ba0ba19a4946c3d12e64d8a @ 0x4D0  (System.Boolean)
//   %3d940025c37fe62498927eb0a56c1500c093f7c7 @ 0x4D1  (System.Boolean)
//   %e403f3282e044fbbe9ccc8b3febe1717c7af7ba3 @ 0x4D8  (UnityEngine.Transform[])
//   %c09bc1110c9175fd3242e3f2d5ff5c28ff797f94 @ 0x4E0  (System.Boolean)
//   %2a66edcad6675fc40f5f40c5280d88c002523e04 @ 0x4E4  (PlayerModel.%5770a04454fdb58a270c2e02e49a019cc241727a)
//   %331729e6342702a73e7c9aafc504c3fad5b0003c @ 0x4EC  (System.Boolean)
//   %5ceb046e2d42448b645f46a0a7bc2b8ffd79bd2e @ 0x4ED  (System.Boolean)
//   %e80614b421cffe7d1f2a2652a1e7a696cdd995ac @ 0x4F0  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %5047328667cc4626756faa035bd7178727e07898 @ 0x4F4  (%0d293ed25c0aac1226694e96e3766c7a4e601aec)
//   %c41c55b74b0ccf49f3ba556aecf662061c4c0732 @ 0x4F8  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %cfff29545b9d3a8059d8fe0ffa4147a29a932f65 @ 0x4FC  (UnityEngine.Vector3)
//   %5221235909e0e32cd206389ab4fbb6379264d4fb @ 0x508  (UnityEngine.Vector3)
//   %ea39bdfa38e2dd87373904c9725a661f1b61d362 @ 0x514  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %deebda59e3ccc63e69f070b30eb9c52d0bff01ac @ 0x518  (UnityEngine.Vector3)
//   %592dce2cd46b268b820af6db9c924e7ef6725b95 @ 0x524  (UnityEngine.Vector3)
//   %efbed46efca45ea60e2ce8c3fd171f5757009953 @ 0x530  (%b05837bf129cd4260975fabd3fa5ddae6563969f)

// raw class: BaseMovement (label=BaseMovement klass=000001BC03B2FE80 instance_fields=10)
//   %8950c873f16373e38e85034e6520b74589df73ab @ 0x020  (System.Boolean)
//   %a095f21b60c68e23d579643e829cb08eb1073633 @ 0x024  (System.Single)
//   %76ba65f37134949e03651144a5ddb02bec13e74d @ 0x028  (BasePlayer)
//   %9d87f0ce62b15f4806dbf8ac7f3b3b231e61214c @ 0x030  (UnityEngine.Vector3)
//   %3418eed241dd079eba933b107698be47113de343 @ 0x03C  (UnityEngine.Vector3)
//   %5c43d173c8f8079906fa7bef6aab058e35eec862 @ 0x048  (System.Single)
//   %18aae733c4ad83c300e51a2461ff17135bea0d6c @ 0x04C  (System.Single)
//   %0c58e5a58e0381322ea85a1f1a3b6d52458a8ac5 @ 0x050  (System.Single)
//   %84e86f7c152308722a802b9f2d492391af2466c3 @ 0x054  (System.Single)
//   %99ec84f195ff9fc0cae5ccaeca522bd1a956c534 @ 0x058  (System.Single)

// raw class: PlayerMovement NOT FOUND

// raw class: PlayerEyes (label=PlayerEyes klass=000001BC04121410 instance_fields=9)
//   thirdPersonSleepingOffset                @ 0x028  (UnityEngine.Vector3)
//   defaultLazyAim                           @ 0x038  (LazyAimProperties)
//   %4b00325db1243f0a9411bb0ba0023da859febd7d @ 0x040  (%2cad33a9772366eb0a6a4a01a4bc6b2f8abeafd6<UnityEngine.Vector3>)
//   %bb137aa743730a89bc4e4040d9c461272ea1e296 @ 0x050  (UnityEngine.Quaternion)
//   %51697c96b46b39d1c6455d9275216aa078a34e64 @ 0x060  (UnityEngine.Vector3)
//   %7a9b0ac6917c9fdab2e4621111e6e76237c4e135 @ 0x06C  (UnityEngine.Quaternion)
//   %b552d41cc5307cdd782b75eb7b8bc32952baa7ef @ 0x07C  (UnityEngine.Quaternion)
//   %e67d3c84623fb222a165273036312b85bd581369 @ 0x08C  (System.Single)
//   %064615543b8147a4d831347a7f99ccbe2e61d427 @ 0x090  (System.Boolean)

// raw class: PlayerInput (label=PlayerInput klass=000001BC03034340 instance_fields=24)
//   %a6d87ef55c108b3f983ada8c9cb3771c003a5342 @ 0x028  (%499627f0f61d23d1cf7c844ab08fdc2666f19268)
//   %6833cc6f68fc44b9d207558eb72b4fba6c221f53 @ 0x030  (System.Boolean)
//   %b8a198eb4dd42919b5a0faae7b69aa2ee13b179d @ 0x034  (UnityEngine.Quaternion)
//   %02fbe19a87077255ac0fdf36eb32565eb0187910 @ 0x044  (UnityEngine.Vector3)
//   %87dcd79754505e3aed1a68e6c771c0ba7859c149 @ 0x050  (UnityEngine.Vector3)
//   %d2c2aaa5c9f959b3af0b0c2be0c2f15e00ac96d4 @ 0x05C  (System.Boolean)
//   %d2e86cc786da6c111894a743c9eb91d3811204ec @ 0x060  (System.Single)
//   %7b46de337430ba8873f6b1e559a97bdecb3dd1dc @ 0x064  (UnityEngine.Quaternion)
//   %70c0566b7bbc21283b1b9b282e7848233e42f639 @ 0x074  (UnityEngine.Vector3)
//   %fc1fb01726da3b6c575b62abb79f27e9cf3658ab @ 0x080  (%2cad33a9772366eb0a6a4a01a4bc6b2f8abeafd6<UnityEngine.Vector3>)
//   %dea6945bac34b195c8cc2df2d748ffe28ee082f2 @ 0x090  (UnityEngine.Vector2)
//   %e5f215bff4764be0b1679e69ca7693e1c51ace6a @ 0x098  (System.Single)
//   %c92a0553b0ad3f96d8f82c4444cc133f8a3910d1 @ 0x09C  (System.Int32)
//   %8f74ad631b99ff66e2f96029c268ea4a85c647c5 @ 0x0A0  (System.Int32)
//   %74f559d174cff545fd0ba2f3c794249a05be2012 @ 0x0A4  (System.Boolean)
//   %56817be517d579bd81236ca139ab8420301796a0 @ 0x0A5  (System.Boolean)
//   %1679c246bbc6e2a4810c7a254ff78b37462b2c83 @ 0x0A6  (System.Boolean)
//   %11ba161988cf528a37a4c82e06183e44a8d4c256 @ 0x0A7  (System.Boolean)
//   %d723110981a757000a80e62aaa842f2fdc23ac38 @ 0x0A8  (System.Boolean)
//   %ebfa93e14a54508df61fbbb9639d61a5b657f3e5 @ 0x0B0  (%67d634f6be42874742008e503701166635022425)
//   %8d663db12ac930a623fc171825754a1b478547f0 @ 0x0B8  (UnityEngine.Vector3)
//   %3162e718a8c91213270ca5dbf5328b1877340310 @ 0x0C4  (UnityEngine.Vector3)
//   %2ee7c6ce3f597a26aed3d657498fa1f97642421b @ 0x0D0  (System.Int32)
//   %0bcba7afc3705113c86d195e1852e06953355466 @ 0x0D4  (System.Boolean)

// raw class: ModelState NOT FOUND

// raw class: %b113032ac4a442f38927954dbb21a8d28d88510c (label=Item klass=000001BC003562B0 instance_fields=31)
//   %1c93cd5438568e6f00c5a22ae4153399ecee0395 @ 0x010  (System.UInt32)
//   %dcdbf1dfd60b65bba88a13cb3c7052dbf18cd9fe @ 0x018  (%1bd0e43aa1d533f14f7abcdd53ac06fa68f779a1)
//   %251b0a741a166de31cdb20d5717f835f7b062ce7 @ 0x020  (System.Collections.Generic.List<%29fcc42a8682a78b7747c73572d26bbabeb07bb3>)
//   %f3f0d3c58036a5ea79a92e6fa3260387022ade88 @ 0x028  (System.String)
//   %9fa16afe849aec712d17fe4a4d6ea0e4f847cdf5 @ 0x030  (System.Single)
//   %7ae981bc5e19f9554779ef8cde6928890d8479d9 @ 0x038  (System.String)
//   %a1e00c6ab7cb8e7e581ebaece7d979758a4f96e3 @ 0x040  (System.Boolean)
//   %2464d7a72ea988004030acc3e295ceb43380d483 @ 0x044  (System.Single)
//   %afd544ca025f886b65e2ea01195d8ac79d733cf8 @ 0x048  (%91f5897cc0e90474f41909c855d8a1c8b087e582)
//   %eee10368eedda8557f13c998719a79dd0e69b4b4 @ 0x058  (System.Single)
//   %d83083f44b43c5d9659c0b964a26b5e614bf4d67 @ 0x060  (%1d6a0aa2fe65126c6a31d6af1a48dc120315dc35)
//   %e9839d2c7eee60bd9486cb6cbe3fcc9679a04a33 @ 0x068  (System.Int32)
//   %cc304a8fced0acd473f9808c246cee65962d1008 @ 0x070  (%91f5897cc0e90474f41909c855d8a1c8b087e582)
//   %8650133c24aca034c69e1acffeec2db7dc72ed5c @ 0x080  (System.String)
//   %f654713ecfbf17271d86e147e6cf50c7c099b3fc @ 0x088  (%b113032ac4a442f38927954dbb21a8d28d88510c.Flag)
//   %1c81d9a73fbfea370458f1b91afac3a28ef9cb6c @ 0x08C  (System.Single)
//   %7ff3ac3f1e3c88bc6cd53e1a78641a78c6f76163 @ 0x090  (System.UInt64)
//   %f1e62c4360c8bfe8077cadd5f1fa5587d48dacdd @ 0x098  (System.UInt64)
//   %d81338b7bae6ab21099a5d3474d0006e052a01fd @ 0x0A0  (ItemDefinition)
//   %69dc7ed0b25bb8eca520daf7e027fbabed10963e @ 0x0A8  (%1bd0e43aa1d533f14f7abcdd53ac06fa68f779a1)
//   %25871f915253990a1f1736aa9a42729af980e00e @ 0x0B0  (System.Single)
//   %cb8616578076178d21193ae71785e6b3e06fbcee @ 0x0B4  (System.Single)
//   %f39659eed456623626a8970898c660a6ede9e26a @ 0x0B8  (System.Action<%b113032ac4a442f38927954dbb21a8d28d88510c>)
//   %a3d4887712e7117da362f73dfc13dd5cb9d83c88 @ 0x0C0  (System.Boolean)
//   %6b7b2a21816330ba634f30221d9c99d6fc8f69f1 @ 0x0C4  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %00038f6177032c3e5300f2b3dfd3e07463974518 @ 0x0C8  (System.Single)
//   %84c53be7b99195108e2980cfe0aa13be0b3e8b71 @ 0x0CC  (System.Single)
//   %9b635752764373e3bed8dbaa226695c636825a0e @ 0x0D0  (%b7d55f00acfb2845d7716544d980a86146ccc307.%d0ee058dc96adbf50a0d08bcbde52fe88cd7917f)
//   %8764da92399b568c10d96df93e904a695598be03 @ 0x0D8  (System.Nullable<System.Int32>)
//   %7e95736b749d254f2a248c4433da4b68871f77a4 @ 0x0E0  (System.Int32)
//   %6841a6ede4a675b35413418edcbc4b8594eb4dc9 @ 0x0E4  (System.Nullable<System.Int32>)

// raw class: %1d6a0aa2fe65126c6a31d6af1a48dc120315dc35 (label=ItemId klass=000001BC00356F80 instance_fields=1)
//   %ffd99cb7d4cf875e5d1e15b81138a0b2c35dd30a @ 0x010  (System.UInt64)

// raw class: ItemDefinition (label=ItemDefinition klass=000001BC03A001D0 instance_fields=62)
//   itemid                                   @ 0x020  (System.Int32)
//   shortname                                @ 0x028  (System.String)
//   era                                      @ 0x030  (Rust.Era)
//   eraRestrictions                          @ 0x034  (Rust.EraRestriction)
//   lootDistributionType                     @ 0x038  (ItemDefinition.LootDistributionModifierType)
//   displayName                              @ 0x040  (%7f632395dd52341c069ed0683b05893b38f6577d.Phrase)
//   displayDescription                       @ 0x048  (%7f632395dd52341c069ed0683b05893b38f6577d.Phrase)
//   iconSprite                               @ 0x050  (UnityEngine.Sprite)
//   category                                 @ 0x058  (ItemCategory)
//   selectionPanel                           @ 0x05C  (ItemSelectionPanel)
//   vehicleItem                              @ 0x060  (System.Boolean)
//   vehicleCategory                          @ 0x064  (VehicleCategory)
//   maxDraggable                             @ 0x068  (System.Int32)
//   itemType                                 @ 0x06C  (%1bd0e43aa1d533f14f7abcdd53ac06fa68f779a1.ContentsType)
//   amountType                               @ 0x070  (ItemDefinition.AmountType)
//   occupySlots                              @ 0x074  (ItemSlot)
//   stackable                                @ 0x078  (System.Int32)
//   volume                                   @ 0x07C  (System.Int32)
//   baseRadioactivity                        @ 0x080  (System.Single)
//   %c1fb0cf0e4f5f123dc23fde87aabe82f30acca83 @ 0x084  (System.Single)
//   quickDespawn                             @ 0x088  (System.Boolean)
//   blockStealingInSafeZone                  @ 0x089  (System.Boolean)
//   allowBurying                             @ 0x08A  (System.Boolean)
//   tutorialAllowance                        @ 0x08C  (BasePlayer.TutorialItemAllowance)
//   supportsStackableOwnership               @ 0x090  (System.Boolean)
//   rarity                                   @ 0x094  (Rust.Rarity)
//   despawnRarity                            @ 0x098  (Rust.Rarity)
//   spawnAsBlueprint                         @ 0x09C  (System.Boolean)
//   inventoryGrabSound                       @ 0x0A0  (SoundDefinition)
//   inventoryDropSound                       @ 0x0A8  (SoundDefinition)
//   physImpactSoundDef                       @ 0x0B0  (SoundDefinition)
//   condition                                @ 0x0B8  (ItemDefinition.Condition)
//   hidden                                   @ 0x0E0  (System.Boolean)
//   flags                                    @ 0x0E4  (ItemDefinition.Flag)
//   hideSelectedPanel                        @ 0x0E8  (System.Boolean)
//   steamItem                                @ 0x0F0  (SteamInventoryItem)
//   steamDlc                                 @ 0x0F8  (SteamDLCItem)
//   supportsAccessories                      @ 0x100  (System.Boolean)
//   Parent                                   @ 0x108  (ItemDefinition)
//   worldModelPrefab                         @ 0x110  (GameObjectRef)
//   worldModelOverrides                      @ 0x118  (ItemDefinition.OverrideWorldModel[])
//   treatAsComponentForRepairs               @ 0x120  (System.Boolean)
//   AlignWorldModelOnDrop                    @ 0x121  (System.Boolean)
//   WorldModelDropOffset                     @ 0x124  (UnityEngine.Vector3)
//   AdjustCenterOfMassOnDrop                 @ 0x130  (System.Boolean)
//   DropCenterOfMass                         @ 0x134  (UnityEngine.Vector3)
//   isRedirectOf                             @ 0x140  (ItemDefinition)
//   redirectVendingBehaviour                 @ 0x148  (ItemDefinition.RedirectVendingBehaviour)
//   %6ea39faa1854291c632bc8d0450870fa0fc9ddd9 @ 0x150  (ItemModCookable)
//   Traits                                   @ 0x158  (BaseEntity.TraitFlag)
//   skins                                    @ 0x160  (ItemSkinDirectory.Skin[])
//   %047446bd159ea6cd496d1a71c33c45bb9dfc0be7 @ 0x168  (ItemBlueprint)
//   panel                                    @ 0x170  (UnityEngine.GameObject)
//   %3573204cebaa8630035477f677f3566d0fd56e6a @ 0x178  (ItemMod[])
//   %472c827012a2d5f9a69d9a5a51beb6cd888fd21c @ 0x180  (ItemModSpriteConfig)
//   %85ded0a9c5e9df2b087e9d86bacc6e99e8b3ad49 @ 0x188  (%a6b8a14efcf809fef81d78646caeb9456dcb703b[])
//   %e03e14c2383cadaaf5aa4bdc921b6713b1d4d475 @ 0x190  (ItemModWearable)
//   %31334d15b51c472c99563fac4f4fc0d3a2d3d8d8 @ 0x198  (ItemDefinition[])
//   %954c4e3377083dc331acf3f801c23f075c273d81 @ 0x1A0  (System.Boolean)
//   %b874c0436e8a604e12ab447f4a64b33240d54739 @ 0x1A1  (System.Boolean)
//   %5f23af65023d5bab1519e5315bfd4b1adae5947c @ 0x1A2  (System.Boolean)
//   %fd028bd0807920b99ce8546b04b0ed67579fa1af @ 0x1A8  (ItemModBurnable)

// raw class: ItemModContainer (label=ItemModContainer klass=000001BC02365E10 instance_fields=18)
//   capacity                                 @ 0x030  (System.Int32)
//   maxStackSize                             @ 0x034  (System.Int32)
//   containerVolume                          @ 0x038  (System.Int32)
//   canLootInWorld                           @ 0x03C  (System.Boolean)
//   pickupInWorldDelay                       @ 0x040  (System.Single)
//   maxWeight                                @ 0x044  (System.Single)
//   worldWeightScale                         @ 0x048  (System.Single)
//   containerFlags                           @ 0x04C  (%1bd0e43aa1d533f14f7abcdd53ac06fa68f779a1.Flag)
//   onlyAllowedContents                      @ 0x050  (%1bd0e43aa1d533f14f7abcdd53ac06fa68f779a1.ContentsType)
//   onlyAllowedItemType                      @ 0x058  (ItemDefinition)
//   availableSlots                           @ 0x060  (System.Collections.Generic.List<ItemSlot>)
//   validItemWhitelist                       @ 0x068  (ItemDefinition[])
//   openInDeployed                           @ 0x070  (System.Boolean)
//   openInInventory                          @ 0x071  (System.Boolean)
//   defaultContents                          @ 0x078  (System.Collections.Generic.List<ItemAmount>)
//   blockAmmoSource                          @ 0x080  (System.Boolean)
//   openSound                                @ 0x088  (SoundDefinition)
//   closeSound                               @ 0x090  (SoundDefinition)

// raw class: ItemModProjectile (label=ItemModProjectile klass=000001BC03B2DA80 instance_fields=14)
//   projectileObject                         @ 0x020  (GameObjectRef)
//   mods                                     @ 0x028  (ItemModProjectileMod[])
//   ammoType                                 @ 0x030  (Rust.AmmoTypes)
//   ammoSubType                              @ 0x034  (Rust.AmmoSubTypes)
//   numProjectiles                           @ 0x038  (System.Int32)
//   projectileSpread                         @ 0x03C  (System.Single)
//   projectileVelocity                       @ 0x040  (System.Single)
//   projectileVelocitySpread                 @ 0x044  (System.Single)
//   useCurve                                 @ 0x048  (System.Boolean)
//   spreadScalar                             @ 0x050  (UnityEngine.AnimationCurve)
//   attackEffectOverride                     @ 0x058  (GameObjectRef)
//   barrelConditionLoss                      @ 0x060  (System.Single)
//   category                                 @ 0x068  (System.String)
//   SkinOverrides                            @ 0x070  (ItemModProjectile.SkinOverride[])

// raw class: HeldEntity (label=HeldEntity klass=000001BC00C60D10 instance_fields=33)
//   %81decfccd09aa78c949dc57faf29b023eaf20207 @ 0x1F0  (%b113032ac4a442f38927954dbb21a8d28d88510c)
//   %0370137b14985de9b91f5f732891b33eefd37448 @ 0x1F8  (UnityEngine.Vector3)
//   %885a4127f9d5aa23aca73e4b1a06d36e0876ed48 @ 0x204  (System.Single)
//   worldModelAnimator                       @ 0x208  (UnityEngine.Animator)
//   thirdPersonDeploySound                   @ 0x210  (SoundDefinition)
//   thirdPersonAimSound                      @ 0x218  (SoundDefinition)
//   thirdPersonAimEndSound                   @ 0x220  (SoundDefinition)
//   hideViewmodel                            @ 0x228  (System.Boolean)
//   %8d5a79c7fdfed06b32f03217364a8b3a9b20dc88 @ 0x230  (System.Collections.Generic.List<HeldEntity.%5eb1a4a0cc7e9d6b189387527dcc793334ab02d4>)
//   %832d1fb1bbb0bb7e96758b9993029fcc99d4377a @ 0x238  (System.Boolean)
//   %6770463bf9cca22cb9e719752cbac737697236b3 @ 0x239  (System.Boolean)
//   %2ee608ab6fc30848a575fc7cee152d6c6bc16434 @ 0x23A  (System.Boolean)
//   %9e3b5589c8cf38c15b7366b9e637c5d615bfa818 @ 0x23B  (System.Boolean)
//   %eaebf1f6c84b1493f625d39190e0a35307bbd304 @ 0x240  (ViewModel)
//   %edf76f74dd81ce3124e6020fac476942ac64aaa5 @ 0x248  (System.Single)
//   handBone                                 @ 0x250  (System.String)
//   HoldAnimationOverride                    @ 0x258  (UnityEngine.AnimatorOverrideController)
//   holdInfo                                 @ 0x260  (HeldEntity.HoldInfo)
//   isBuildingTool                           @ 0x27C  (System.Boolean)
//   canBeUsedWithShield                      @ 0x27D  (System.Boolean)
//   ForwardSignalsFromPlayer                 @ 0x27E  (System.Boolean)
//   forcedOwner                              @ 0x280  (BasePlayer)
//   useOwnerForward                          @ 0x288  (System.Boolean)
//   CanSetLightsOn                           @ 0x289  (System.Boolean)
//   holsterInfo                              @ 0x290  (HeldEntity.HolsterInfo)
//   HeldCameraMode                           @ 0x298  (BasePlayer.CameraMode)
//   hostileScore                             @ 0x29C  (System.Single)
//   FirstPersonArmOffset                     @ 0x2A0  (UnityEngine.Vector3)
//   FirstPersonArmRotation                   @ 0x2AC  (UnityEngine.Vector3)
//   FirstPersonRotationStrength              @ 0x2B8  (System.Single)
//   AttachmentAnchor                         @ 0x2C0  (UnityEngine.Transform)
//   %c54e68abb0e8da33aad7a7c002334c0c774a3ec4 @ 0x2C8  (Attachment)
//   %51a73d2f2f4ced17fbeef1fa2dd1e0893d7c9a0a @ 0x2D0  (%1d6a0aa2fe65126c6a31d6af1a48dc120315dc35)

// raw class: BaseProjectile (label=BaseProjectile klass=000001BC0253F0C0 instance_fields=71)
//   NoiseRadius                              @ 0x370  (System.Single)
//   damageScale                              @ 0x374  (System.Single)
//   distanceScale                            @ 0x378  (System.Single)
//   projectileVelocityScale                  @ 0x37C  (System.Single)
//   automatic                                @ 0x380  (System.Boolean)
//   usableByTurret                           @ 0x381  (System.Boolean)
//   turretDamageScale                        @ 0x384  (System.Single)
//   largeTurretWeapon                        @ 0x388  (System.Boolean)
//   turretReloadDurationOverride             @ 0x38C  (System.Single)
//   maxAttackEffectDistance                  @ 0x390  (System.Single)
//   attackFX                                 @ 0x398  (GameObjectRef)
//   silencedAttack                           @ 0x3A0  (GameObjectRef)
//   muzzleBrakeAttack                        @ 0x3A8  (GameObjectRef)
//   fireModeSound                            @ 0x3B0  (SoundDefinition)
//   MuzzlePoint                              @ 0x3B8  (UnityEngine.Transform)
//   reloadTime                               @ 0x3C0  (System.Single)
//   canUnloadAmmo                            @ 0x3C4  (System.Boolean)
//   primaryMagazine                          @ 0x3C8  (BaseProjectile.Magazine)
//   fractionalReload                         @ 0x3D0  (System.Boolean)
//   reloadStartDuration                      @ 0x3D4  (System.Single)
//   reloadFractionDuration                   @ 0x3D8  (System.Single)
//   reloadEndDuration                        @ 0x3DC  (System.Single)
//   alternateDryFireRate                     @ 0x3E0  (System.Single)
//   sendReloadSignalFromServer               @ 0x3E4  (System.Boolean)
//   aimSway                                  @ 0x3E8  (System.Single)
//   aimSwaySpeed                             @ 0x3EC  (System.Single)
//   recoil                                   @ 0x3F0  (RecoilProperties)
//   aimconeCurve                             @ 0x3F8  (UnityEngine.AnimationCurve)
//   aimCone                                  @ 0x400  (System.Single)
//   hipAimCone                               @ 0x404  (System.Single)
//   aimconePenaltyPerShot                    @ 0x408  (System.Single)
//   aimConePenaltyMax                        @ 0x40C  (System.Single)
//   aimconePenaltyRecoverTime                @ 0x410  (System.Single)
//   aimconePenaltyRecoverDelay               @ 0x414  (System.Single)
//   stancePenaltyScale                       @ 0x418  (System.Single)
//   hasADS                                   @ 0x41C  (System.Boolean)
//   noAimingWhileCycling                     @ 0x41D  (System.Boolean)
//   manualCycle                              @ 0x41E  (System.Boolean)
//   CrosshairSettings                        @ 0x420  (BaseProjectile.WeaponCrosshairSettings)
//   %9f0e3cadbbb313e1ec7abb027fc1fe0aafe34b53 @ 0x424  (System.Boolean)
//   %c9c4d8785397b94d6cd0cf8d884777fdca8aa838 @ 0x425  (System.Boolean)
//   %0a29dcf100f634af8a876682c5858856d59b5181 @ 0x426  (System.Boolean)
//   isBurstWeapon                            @ 0x427  (System.Boolean)
//   canChangeFireModes                       @ 0x428  (System.Boolean)
//   defaultOn                                @ 0x429  (System.Boolean)
//   internalBurstRecoilScale                 @ 0x42C  (System.Single)
//   internalBurstFireRateScale               @ 0x430  (System.Single)
//   internalBurstAimConeScale                @ 0x434  (System.Single)
//   resetDuration                            @ 0x438  (System.Single)
//   numShotsFired                            @ 0x43C  (System.Int32)
//   %f749d7e09387e27863049911c5630f4cf0f7997b @ 0x440  (%2cad33a9772366eb0a6a4a01a4bc6b2f8abeafd6<System.Single>)
//   %67fecb16dd57f0deec97921c6857b5f0ef87a8a3 @ 0x448  (%2cad33a9772366eb0a6a4a01a4bc6b2f8abeafd6<System.Single>)
//   %3bd080bdf13ccdc3012f381fe9973260a1c16ad2 @ 0x450  (System.Single)
//   %70635f2fbdf977e964bd3f2e129885dd3a244302 @ 0x454  (System.Single)
//   %01edb75ef45d0abc5012fd6a558ef8bb95fb99e1 @ 0x458  (System.UInt32)
//   %4d1acbf41bede897c641d53241dba91965ee1ccb @ 0x45C  (System.Single)
//   %159eeaa65888cbe3713fc547ed9a414c4adf7011 @ 0x460  (System.Single)
//   %a1c6f76f0cd15a720d481fb6187959c0b2b7e575 @ 0x464  (System.Single)
//   %ad5765b0cfebd6e8d10b6f3d9d6b4ea3e85f0578 @ 0x468  (System.Single)
//   %a2cbb1f4dec7acf1c3ad9f1a5ee517883035066a @ 0x46C  (System.Boolean)
//   %1f15ef30272eded512e461ce08e3ffb6f02fb386 @ 0x470  (System.Single)
//   %bacff10a53d69e09338bd4861a8748506ee80998 @ 0x474  (%2cad33a9772366eb0a6a4a01a4bc6b2f8abeafd6<System.Single>)
//   %c1aac8f45d682a537034faf91732cfd29e6a4ff4 @ 0x47C  (System.Single)
//   %265d9d51d33f7a29b8ac5be89940a4d11477f00c @ 0x480  (%0d293ed25c0aac1226694e96e3766c7a4e601aec)
//   %01c8e88341899c239c47a31e1dd8f281632b2990 @ 0x484  (System.Int32)
//   %5ba6a7f88158df5594eeac48d9c6fc3d9d18f1c5 @ 0x488  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)
//   %47f012312b26d10bbf30051b2a23fe5ffd1ab24e @ 0x490  (ItemDefinition)
//   %072df51eaf1b15b866486f10966b5f1a76377353 @ 0x498  (System.Int32)
//   %a497dd2e36344ca8847dfbdeef7995d0ca0e26f9 @ 0x49C  (System.Int32)
//   %496e2e54b26347a5f1d426b5d37be65c52b3203b @ 0x4A0  (System.Int32)
//   %08a4a6aef1ab59b50252a012b9dbdde50d7ec54e @ 0x4A4  (System.Boolean)

// raw class: BaseLauncher (label=BaseLauncher klass=000001BC02988610 instance_fields=3)
//   initialSpeedMultiplier                   @ 0x4A8  (System.Single)
//   %61a943c20c17474c75c77d372274f7e5214a0fa6 @ 0x4AC  (System.Int32)
//   %be5c3c8b891f4be6490d681281e5693dfc222e91 @ 0x4B0  (%83b4e6d678cd9a4c3ec4878b701120be14f6f33c)

// raw class: BaseMelee (label=BaseMelee klass=000001BC00C55EB0 instance_fields=24)
//   canThrowAsProjectile                     @ 0x370  (System.Boolean)
//   canThrowAsEntity                         @ 0x371  (System.Boolean)
//   canAiHearIt                              @ 0x372  (System.Boolean)
//   canScareAiWhenAimed                      @ 0x373  (System.Boolean)
//   onlyThrowAsProjectile                    @ 0x374  (System.Boolean)
//   ThrowFullStack                           @ 0x375  (System.Boolean)
//   damageProperties                         @ 0x378  (DamageProperties)
//   damageTypes                              @ 0x380  (System.Collections.Generic.List<Rust.DamageTypeEntry>)
//   deployableDamageOverrides                @ 0x388  (System.Collections.Generic.List<Rust.DamageTypeEntry>)
//   maxDistance                              @ 0x390  (System.Single)
//   attackRadius                             @ 0x394  (System.Single)
//   isAutomatic                              @ 0x398  (System.Boolean)
//   blockSprintOnAttack                      @ 0x399  (System.Boolean)
//   canUntieCrates                           @ 0x39A  (System.Boolean)
//   longResourceForgiveness                  @ 0x39B  (System.Boolean)
//   PlayerAnimSystem                         @ 0x3A0  (MeleeWeaponAnimationSubSystem)
//   strikeFX                                 @ 0x3A8  (GameObjectRef)
//   useStandardHitEffects                    @ 0x3B0  (System.Boolean)
//   aiStrikeDelay                            @ 0x3B4  (System.Single)
//   swingEffect                              @ 0x3B8  (GameObjectRef)
//   materialStrikeFX                         @ 0x3C0  (System.Collections.Generic.List<BaseMelee.MaterialFX>)
//   heartStress                              @ 0x3C8  (System.Single)
//   gathering                                @ 0x3D0  (ResourceDispenser.GatherProperties)
//   %df92e22f801c716586a9ce3046e0e285239b959b @ 0x3D8  (System.Boolean)

// raw class: RecoilProperties (label=RecoilProperties klass=000001BC04417520 instance_fields=22)
//   recoilYawMin                             @ 0x018  (System.Single)
//   recoilYawMax                             @ 0x01C  (System.Single)
//   recoilPitchMin                           @ 0x020  (System.Single)
//   recoilPitchMax                           @ 0x024  (System.Single)
//   timeToTakeMin                            @ 0x028  (System.Single)
//   timeToTakeMax                            @ 0x02C  (System.Single)
//   ADSScale                                 @ 0x030  (System.Single)
//   movementPenalty                          @ 0x034  (System.Single)
//   clampPitch                               @ 0x038  (System.Single)
//   pitchCurve                               @ 0x040  (UnityEngine.AnimationCurve)
//   yawCurve                                 @ 0x048  (UnityEngine.AnimationCurve)
//   useCurves                                @ 0x050  (System.Boolean)
//   curvesAsScalar                           @ 0x051  (System.Boolean)
//   shotsUntilMax                            @ 0x054  (System.Int32)
//   maxRecoilRadius                          @ 0x058  (System.Single)
//   overrideAimconeWithCurve                 @ 0x05C  (System.Boolean)
//   aimconeCurveScale                        @ 0x060  (System.Single)
//   aimconeCurve                             @ 0x068  (UnityEngine.AnimationCurve)
//   aimconeProbabilityCurve                  @ 0x070  (UnityEngine.AnimationCurve)
//   ammoAimconeScaleMultiProjectile          @ 0x078  (System.Single)
//   ammoAimconeScaleSingleProjectile         @ 0x07C  (System.Single)
//   newRecoilOverride                        @ 0x080  (RecoilProperties)

// raw class: BaseProjectile.Magazine NOT FOUND

// raw class: BaseProjectile.AmmoTypes NOT FOUND

// raw class: WorldItem (label=WorldItem klass=000001BC00CE1930 instance_fields=2)
//   allowPickup                              @ 0x1F0  (System.Boolean)
//   %a0bfe2cccf61f0e53556087fa45a45a5939f0b1b @ 0x1F8  (%b113032ac4a442f38927954dbb21a8d28d88510c)

// raw class: DroppedItem (label=DroppedItem klass=000001BC00CDD300 instance_fields=4)
//   itemModel                                @ 0x200  (GameObjectRef)
//   splashEffect                             @ 0x208  (GameObjectRef)
//   %eade90a9c1dadd41831d00cae937f143a3aa5e60 @ 0x210  (UnityEngine.Collider)
//   %9d30bf1625f9f873885098b68b2760344f565ad0 @ 0x218  (System.Int32)

// raw class: AutoTurret (label=AutoTurret klass=000001BC00C3E9F0 instance_fields=53)
//   %055e74fe6281bd2994a7b94f7872194e3476c8ef @ 0x398  (System.Action<BasePlayer>)
//   %b1fbe1c2c0d5488dbb043cccbd12342cce357be1 @ 0x3A0  (System.Action<BasePlayer>)
//   %d8eb4a55043abfaee93a971ebc66df9ec904c5a6 @ 0x3A8  (System.Action<BasePlayer>)
//   %dcd0f7200fbb39038de752d5f04a2367e6bef0c7 @ 0x3B0  (System.Action<BasePlayer>)
//   %085504df0181688d18b328f7755b19731bce20ca @ 0x3B8  (System.Action<BasePlayer>)
//   %59942f5da825cbf83a3a6a41b1f97b28db8e53dd @ 0x3C0  (System.Action<BasePlayer>)
//   %8e2364a60d8fec14edbbacc389139c97a40c617a @ 0x3C8  (System.Collections.Generic.HashSet<System.UInt64>)
//   %51caf50144ff131546f660e8e7a703945dad2b65 @ 0x3D0  (System.Action<BasePlayer>)
//   %9b922eebffd74eee05c1bb1df9173ed80bf8450e @ 0x3D8  (SoundModulation.Modulator)
//   gun_fire_effect                          @ 0x3E0  (GameObjectRef)
//   bulletEffect                             @ 0x3E8  (GameObjectRef)
//   bulletSpeed                              @ 0x3F0  (System.Single)
//   ambienceEmitter                          @ 0x3F8  (AmbienceEmitter)
//   playAmbientSounds                        @ 0x400  (System.Boolean)
//   assignDialog                             @ 0x408  (UnityEngine.GameObject)
//   laserBeam                                @ 0x410  (LaserBeam)
//   %2c702b697b7dcef428299a9d37b78a5127c219fd @ 0x418  (System.Action<BasePlayer>)
//   %7080154123150174786c015f4266c28e750677f5 @ 0x420  (System.Action<BasePlayer>)
//   %b2af7a8acb4ada08f1b56e1d975c6478187ed2f6 @ 0x428  (System.Single)
//   %5096fbdc3df34312b336ef9732dcf9d6328b8897 @ 0x42C  (System.Boolean)
//   %42215a5bee7482921e82ea0c1c1d5c3559269f54 @ 0x430  (UnityEngine.Quaternion)
//   rcTurnSensitivity                        @ 0x440  (System.Single)
//   RCEyes                                   @ 0x448  (UnityEngine.Transform)
//   IDPanelPrefab                            @ 0x450  (GameObjectRef)
//   rcControls                               @ 0x458  (RemoteControllableControls)
//   rcIdentifier                             @ 0x460  (System.String)
//   %829406cbd00d9df8b056d1d905e449f643e85b09 @ 0x468  (%86139426fbc49b13d9ed7b5c1271168be6670fa4)
//   targetTrigger                            @ 0x470  (TargetTrigger)
//   interferenceTrigger                      @ 0x478  (TriggerBase)
//   maxInterference                          @ 0x480  (System.Single)
//   attachedWeaponZOffsetScale               @ 0x484  (System.Single)
//   socketTransform                          @ 0x488  (UnityEngine.Transform)
//   target                                   @ 0x490  (BaseCombatEntity)
//   eyePos                                   @ 0x498  (UnityEngine.Transform)
//   muzzlePos                                @ 0x4A0  (UnityEngine.Transform)
//   aimDir                                   @ 0x4A8  (UnityEngine.Vector3)
//   gun_yaw                                  @ 0x4B8  (UnityEngine.Transform)
//   gun_pitch                                @ 0x4C0  (UnityEngine.Transform)
//   sightRange                               @ 0x4C8  (System.Single)
//   turnLoopDef                              @ 0x4D0  (SoundDefinition)
//   movementChangeDef                        @ 0x4D8  (SoundDefinition)
//   ambientLoopDef                           @ 0x4E0  (SoundDefinition)
//   focusCameraDef                           @ 0x4E8  (SoundDefinition)
//   focusSoundFreqMin                        @ 0x4F0  (System.Single)
//   focusSoundFreqMax                        @ 0x4F4  (System.Single)
//   peacekeeperToggleSound                   @ 0x4F8  (GameObjectRef)
//   onlineSound                              @ 0x500  (GameObjectRef)
//   offlineSound                             @ 0x508  (GameObjectRef)
//   targetAcquiredEffect                     @ 0x510  (GameObjectRef)
//   targetLostEffect                         @ 0x518  (GameObjectRef)
//   reloadEffect                             @ 0x520  (GameObjectRef)
//   aimCone                                  @ 0x528  (System.Single)
//   %eca6c0dd02b4eb96dba4f1b8f60cde50453f795c @ 0x530  (Sound)

// raw class: NPCAutoTurret (label=NPCAutoTurret klass=000001BC00C383C0 instance_fields=5)
//   centerMuzzle                             @ 0x538  (UnityEngine.Transform)
//   muzzleLeft                               @ 0x540  (UnityEngine.Transform)
//   muzzleRight                              @ 0x548  (UnityEngine.Transform)
//   useSleeperHostile                        @ 0x550  (System.Boolean)
//   %65373e1ef9183459a9e979763232f0647c38bfaf @ 0x551  (System.Boolean)

// raw class: MainCamera (label=MainCamera klass=000001BC02CAAFF0 instance_fields=0)
//   (no instance fields)

// raw class: CameraState NOT FOUND

// raw class: ConVar_Graphics NOT FOUND

// raw class: Model (label=Model klass=000001BC0302D660 instance_fields=11)
//   collision                                @ 0x020  (UnityEngine.SphereCollider)
//   rootBone                                 @ 0x028  (UnityEngine.Transform)
//   headBone                                 @ 0x030  (UnityEngine.Transform)
//   eyeBone                                  @ 0x038  (UnityEngine.Transform)
//   animator                                 @ 0x040  (UnityEngine.Animator)
//   skeleton                                 @ 0x048  (Facepunch.Skeleton)
//   boneTransforms                           @ 0x050  (UnityEngine.Transform[])
//   boneNames                                @ 0x058  (System.String[])
//   %e09e66e80eba0d0b300f7df46eb61f17f5bedd83 @ 0x060  (UnityEngine.LODGroup)
//   %f1e62c4360c8bfe8077cadd5f1fa5587d48dacdd @ 0x068  (System.Int32)
//   %5ce0ca90a14446f8aa0570833d99725437afd40f @ 0x070  (%c0975438a501a5fc26b5515664d93279b76bfda9)

// raw class: SkinnedMultiMesh (label=SkinnedMultiMesh klass=000001BC03609E80 instance_fields=18)
//   shadowOnly                               @ 0x020  (System.Boolean)
//   %0d7fc81a4b47dd5d90df40d8c2038f39ceee2fba @ 0x021  (System.Boolean)
//   eyesView                                 @ 0x022  (System.Boolean)
//   skeleton                                 @ 0x028  (Facepunch.Skeleton)
//   skeletonSkinLod                          @ 0x030  (Facepunch.SkeletonSkinLod)
//   parts                                    @ 0x038  (System.Collections.Generic.List<SkinnedMultiMesh.%2e7d303351b4f446a62366d6e599553e2c1bf35f>)
//   %015002d0062870bb27a8bb832adf91ce255cc408 @ 0x040  (UnityEngine.MaterialPropertyBlock)
//   %75fe196a88401df5b4a226324bd317bac3674c5e @ 0x048  (System.Int64)
//   %37b6ed7e1991f583ea57862dd2611549ce5a79b5 @ 0x050  (UnityEngine.MaterialPropertyBlock)
//   %b248d598635e334d860be79723714b1f8a981713 @ 0x058  (System.Collections.Generic.List<UnityEngine.Renderer>)
//   skinNumber                               @ 0x060  (System.Single)
//   meshNumber                               @ 0x064  (System.Single)
//   meshSubNumber                            @ 0x068  (System.Single)
//   hairNumber                               @ 0x06C  (System.Single)
//   dyeNumber                                @ 0x070  (System.Single)
//   skinType                                 @ 0x074  (System.Int32)
//   SkinCollection                           @ 0x078  (SkinSetCollection)
//   %3a515c3c1255fd9d7ae445e76e4e40b5e275c872 @ 0x080  (System.Collections.Generic.List<SkinnedMultiMesh.%2e7d303351b4f446a62366d6e599553e2c1bf35f>)

// raw class: PlayerVisualState NOT FOUND


// ===========================================================================
// il2cpp_gchandle_get_target raw bytes
// Use this to hand-derive the current il2cpp handle lookup when Unity
// changes the internal GC handle table layout.
// ===========================================================================
// il2cpp_gchandle_get_target: address=0x7FF852A45CD0 rva=0x845CD0
//   +0x000  E9 6B 74 FD FF CC CC CC CC CC CC CC CC CC CC CC 
//   +0x010  48 83 EC 38 48 89 4C 24 20 48 8D 0D 70 A7 F9 FF 
//   +0x020  48 89 54 24 28 48 8D 54 24 20 E8 61 77 FD FF 48 
//   +0x030  83 C4 38 C3 CC CC CC CC CC CC CC CC CC CC CC CC 
//   +0x040  83 3D A1 56 98 0F 00 4C 8B CA 4C 89 02 74 42 49 
//   +0x050  C1 E9 0C 48 8D 0D D6 08 A2 0F 41 81 E1 FF FF 1F 
//   +0x060  00 41 8B C1 48 C1 E8 06 41 83 E1 3F 48 8D 14 C1 
//   +0x070  0F 0D 0A 0F 1F 40 00 66 0F 1F 84 00 00 00 00 00 
//   +0x080  48 8B 02 48 8B C8 4C 0F AB C9 F0 48 0F B1 0A 75 
//   +0x090  EF C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 
//   +0x0A0  E9 4B 75 FD FF CC CC CC CC CC CC CC CC CC CC CC 
//   +0x0B0  B8 18 00 00 00 C3 CC CC CC CC CC CC CC CC CC CC 
//   +0x0C0  40 53 56 57 41 56 48 83 EC 38 49 8B F9 49 8B F0 
//   +0x0D0  48 8B D9 E8 F8 85 FE FF B9 38 00 00 00 E8 86 F7 
//   +0x0E0  01 00 4C 8B F0 48 89 44 24 20 33 C0 49 89 06 49 
//   +0x0F0  89 46 10 48 8B 94 24 80 00 00 00 49 89 56 28 41 
//   +0x100  89 46 30 49 89 5E 08 49 89 7E 18 49 89 76 20 B9 
//   +0x110  18 00 00 00 E8 4F F7 01 00 48 89 44 24 28 49 8B 
//   +0x120  D6 48 8B C8 E8 47 34 FA FF 90 49 89 06 B9 18 00 
//   +0x130  00 00 E8 31 F7 01 00 48 89 44 24 28 49 8B D6 48 
//   +0x140  8B C8 E8 29 34 FA FF 90 49 89 46 10 49 8B C6 48 
//   +0x150  83 C4 38 41 5E 5F 5E 5B C3 CC CC CC CC CC CC CC 
//   +0x160  40 53 48 83 EC 20 48 8B 42 10 48 8B DA 48 8B 00 
//   +0x170  48 85 C0 74 1B 66 66 66 0F 1F 84 00 00 00 00 00 
//
// hde64 disassembly (first ~0x120 bytes):
//   +0x000  E9 6B 74 FD FF                                   (op=E9)
//   +0x005  CC                                               (op=CC)
