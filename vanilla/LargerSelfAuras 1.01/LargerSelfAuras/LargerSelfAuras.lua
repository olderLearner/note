---LargerSelfAuras---
--TargetFrame_UpdateAuras() and TargetFrame_UpdateAuraPositions() are mostly default Blizzard source.
--The comments in the above 2 funtions are not mine.

LSA = LibStub("AceAddon-3.0"):NewAddon("LargerSelfAuras")
LSAGUI = LibStub("AceGUI-3.0")

local LARGE_AURA_SIZE = 23;	--Self auras (Blizzard default is 21)
local SMALL_AURA_SIZE = 17;	--Others auras (Blizzard default is 17)
local AURA_START_X = 5;
local AURA_START_Y = 32;
local AURA_OFFSET_Y = 1;
local AURA_ROW_WIDTH = 122;
local TOT_AURA_ROW_WIDTH = 101;
local NUM_TOT_AURA_ROWS = 2;
local PLAYER_UNITS = {
	player = true,
	vehicle = true,
	pet = true,
};

function LSA:OnInitialize()
    self.db = LibStub("AceDB-3.0"):New("LSAOptions", LSA.optionDefaults, "Default")
    LibStub("AceConfig-3.0"):RegisterOptionsTable("LargerSelfAuras", LSA.options)
	self.LSAOptions = LibStub("AceConfigDialog-3.0"):AddToBlizOptions("LargerSelfAuras", "LargerSelfAuras")
	LSA:updateVars()
end

function LSA:updateVars()
	if (not self.db.global.enable) then
		--Set local vars back to Blizzard default if "enable" is unticked.
		LARGE_AURA_SIZE = 21;
		SMALL_AURA_SIZE = 17;
	else
		if (self.db.global.selfSize) then
			LARGE_AURA_SIZE = self.db.global.selfSize;
		else 
			LARGE_AURA_SIZE = 23;
		end
		if (self.db.global.otherSize) then
			SMALL_AURA_SIZE = self.db.global.otherSize;
		else 
			SMALL_AURA_SIZE = 17;
		end
	end
	if (TargetFrame) then
		TargetFrame_UpdateAuras(TargetFrame);
	end
end

--The main func they removed from the retail client.
local largeBuffList = {};
local largeDebuffList = {};
function ShouldAuraBeLarge(caster)
	--If enable is unticked disable the resize.
	if (not LSA.db.global.enable) then
		return true;
	end
	if not caster then
		return false;
	end
	for token, value in pairs(PLAYER_UNITS) do
		if UnitIsUnit(caster, token) or UnitIsOwnerOrControllerOfUnit(token, caster) then
			return value;
		end
	end
end

function TargetFrame_UpdateAuras (self)
	local frame, frameName;
	local frameIcon, frameCount, frameCooldown;
	local numBuffs = 0;
	local playerIsTarget = UnitIsUnit(PlayerFrame.unit, self.unit);
	local selfName = self:GetName();
	local canAssist = UnitCanAssist("player", self.unit);

	for i = 1, MAX_TARGET_BUFFS do
        local buffName, icon, count, debuffType, duration, expirationTime, caster, canStealOrPurge, _ , spellId, _, _, casterIsPlayer, nameplateShowAll = UnitBuff(self.unit, i, nil);
        if (buffName) then
            frameName = selfName.."Buff"..(i);
            frame = _G[frameName];
            if ( not frame ) then
                if ( not icon ) then
                    break;
                else
                    frame = CreateFrame("Button", frameName, self, "TargetBuffFrameTemplate");
                    frame.unit = self.unit;
                end
            end
            if ( icon and ( not self.maxBuffs or i <= self.maxBuffs ) ) then
                frame:SetID(i);

                -- set the icon
                frameIcon = _G[frameName.."Icon"];
                frameIcon:SetTexture(icon);

                -- set the count
                frameCount = _G[frameName.."Count"];
                if ( count > 1 and self.showAuraCount ) then
                    frameCount:SetText(count);
                    frameCount:Show();
                else
                    frameCount:Hide();
                end

                -- Handle cooldowns
                --frameCooldown = _G[frameName.."Cooldown"];
                --CooldownFrame_Set(frameCooldown, expirationTime - duration, duration, duration > 0, true);

                -- Show stealable frame if the target is not the current player and the buff is stealable.
                local frameStealable = _G[frameName.."Stealable"];
                if ( not playerIsTarget and canStealOrPurge ) then
                    frameStealable:Show();
                else
                    frameStealable:Hide();
                end

                -- set the buff to be big if the buff is cast by the player or his pet
				numBuffs = numBuffs + 1;
                largeBuffList[numBuffs] = ShouldAuraBeLarge(caster);

                frame:ClearAllPoints();
                frame:Show();
            else
                frame:Hide();
            end
        else
            break;
        end
	end

	for i = numBuffs + 1, MAX_TARGET_BUFFS do
		local frame = _G[selfName.."Buff"..i];
		if ( frame ) then
			frame:Hide();
		else
			break;
		end
	end

	local color;
	local frameBorder;
	local numDebuffs = 0;

	local frameNum = 1;
	local index = 1;

	local maxDebuffs = self.maxDebuffs or MAX_TARGET_DEBUFFS;
	while ( frameNum <= maxDebuffs and index <= maxDebuffs ) do
	    local debuffName, icon, count, debuffType, duration, expirationTime, caster, _, _, _, _, _, casterIsPlayer, nameplateShowAll = UnitDebuff(self.unit, index, "INCLUDE_NAME_PLATE_ONLY");
		if ( debuffName ) then
			if ( TargetFrame_ShouldShowDebuffs(self.unit, caster, nameplateShowAll, casterIsPlayer) ) then
				frameName = selfName.."Debuff"..frameNum;
				frame = _G[frameName];
				if ( icon ) then
					if ( not frame ) then
						frame = CreateFrame("Button", frameName, self, "TargetDebuffFrameTemplate");
						frame.unit = self.unit;
					end
					frame:SetID(index);

					-- set the icon
					frameIcon = _G[frameName.."Icon"];
					frameIcon:SetTexture(icon);

					-- set the count
					frameCount = _G[frameName.."Count"];
					if ( count > 1 and self.showAuraCount ) then
						frameCount:SetText(count);
						frameCount:Show();
					else
						frameCount:Hide();
					end

					-- Handle cooldowns
					--frameCooldown = _G[frameName.."Cooldown"];
					--CooldownFrame_Set(frameCooldown, expirationTime - duration, duration, duration > 0, true);

					-- set debuff type color
					if ( debuffType ) then
						color = DebuffTypeColor[debuffType];
					else
						color = DebuffTypeColor["none"];
					end
					frameBorder = _G[frameName.."Border"];
					frameBorder:SetVertexColor(color.r, color.g, color.b);

					-- set the debuff to be big if the buff is cast by the player or his pet
					numDebuffs = numDebuffs + 1;
					largeDebuffList[numDebuffs] = ShouldAuraBeLarge(caster);

					frame:ClearAllPoints();
					frame:Show();

					frameNum = frameNum + 1;
				end
			end
		else
			break;
		end
		index = index + 1;
	end

	for i = frameNum, MAX_TARGET_DEBUFFS do
		local frame = _G[selfName.."Debuff"..i];
		if ( frame ) then
			frame:Hide();
		else
			break;
		end
	end

	self.auraRows = 0;

	local mirrorAurasVertically = false;
	if ( self.buffsOnTop ) then
		mirrorAurasVertically = true;
	end
	local haveTargetofTarget;
	if ( self.totFrame ) then
		haveTargetofTarget = self.totFrame:IsShown();
	end
	self.spellbarAnchor = nil;
	local maxRowWidth;
	-- update buff positions
	maxRowWidth = ( haveTargetofTarget and self.TOT_AURA_ROW_WIDTH ) or AURA_ROW_WIDTH;
	TargetFrame_UpdateAuraPositions(self, selfName.."Buff", numBuffs, numDebuffs, largeBuffList, TargetFrame_UpdateBuffAnchor, maxRowWidth, 3, mirrorAurasVertically);
	-- update debuff positions
	maxRowWidth = ( haveTargetofTarget and self.auraRows < NUM_TOT_AURA_ROWS and self.TOT_AURA_ROW_WIDTH ) or AURA_ROW_WIDTH;
	TargetFrame_UpdateAuraPositions(self, selfName.."Debuff", numDebuffs, numBuffs, largeDebuffList, TargetFrame_UpdateDebuffAnchor, maxRowWidth, 3, mirrorAurasVertically);
	-- update the spell bar position
	if ( self.spellbar ) then
		Target_Spellbar_AdjustPosition(self.spellbar);
	end
end

function TargetFrame_UpdateAuraPositions(self, auraName, numAuras, numOppositeAuras, largeAuraList, updateFunc, maxRowWidth, offsetX, mirrorAurasVertically)
	-- a lot of this complexity is in place to allow the auras to wrap around the target of target frame if it's shown

	-- Position auras
	local size;
	local offsetY = AURA_OFFSET_Y;
	-- current width of a row, increases as auras are added and resets when a new aura's width exceeds the max row width
	local rowWidth = 0;
	local firstBuffOnRow = 1;
	for i=1, numAuras do
		-- update size and offset info based on large aura status
		if ( largeAuraList[i] ) then
			size = LARGE_AURA_SIZE;
			offsetY = AURA_OFFSET_Y + AURA_OFFSET_Y;
		else
			size = SMALL_AURA_SIZE;
		end

		-- anchor the current aura
		if ( i == 1 ) then
			rowWidth = size;
			self.auraRows = self.auraRows + 1;
		else
			rowWidth = rowWidth + size + offsetX;
		end
		if ( rowWidth > maxRowWidth ) then
			-- this aura would cause the current row to exceed the max row width, so make this aura
			-- the start of a new row instead
			updateFunc(self, auraName, i, numOppositeAuras, firstBuffOnRow, size, offsetX, offsetY, mirrorAurasVertically);

			rowWidth = size;
			self.auraRows = self.auraRows + 1;
			firstBuffOnRow = i;
			offsetY = AURA_OFFSET_Y;

			if ( self.auraRows > NUM_TOT_AURA_ROWS ) then
				-- if we exceed the number of tot rows, then reset the max row width
				-- note: don't have to check if we have tot because AURA_ROW_WIDTH is the default anyway
				maxRowWidth = AURA_ROW_WIDTH;
			end
		else
			updateFunc(self, auraName, i, numOppositeAuras, i - 1, size, offsetX, offsetY, mirrorAurasVertically);
		end
	end
end

---Options---

SLASH_LSAOPTIONSCMD1, SLASH_LSAOPTIONSCMD2 = '/lsa', '/largerselfauras';
function SlashCmdList.LSAOPTIONSCMD(msg, editBox)
	InterfaceOptionsFrame_OpenToCategory("LargerSelfAuras");
	InterfaceOptionsFrame_OpenToCategory("LargerSelfAuras");
end

--Options UI
LSA.options = {
	name = "LargerSelfAuras v" .. GetAddOnMetadata("LargerSelfAuras", "Version"),
	handler = LSA,
	type = 'group',
	args = {
		top_header = {
			type = "description",
			name = "|CffDEDE42设置 (也可输入 /lsa)\n",
			fontSize = "medium",
			order = 1,
		},
		desc = {
			type = "description",
			name = "这里你可以改变你和其他人在目标帧上的光环大小（增益/减益）.\n\n",
			fontSize = "medium",
			order = 2,
		},
		enable = {
			type = "toggle",
			name = "启用",
			desc = "Enable this addon?",
			order = 3,
			get = "getEnable",
			set = "setEnable",
		},
		self = {
			type = "range",
			name = "自己的光环大小",
			desc = "How big should my own auras on the target frame be?",
			order = 4,
			get = "getSelf",
			set = "setSelf",
			min = 10,
			max = 30,
			softMin = 10,
			softMax = 30,
			step = 1,
		},
		other = {
			type = "range",
			name = "其他人的光环大小",
			desc = "How big should other peoples auras on the target frame be?",
			order = 5,
			get = "getOther",
			set = "setOther",
			min = 10,
			max = 30,
			softMin = 10,
			softMax = 30,
			step = 1,
		},
		note = {
			type = "description",
			name = "\n\n\n\nNote: The default sizes from retail wow are 21 self and 17 other, " ..
					"this felt a bit small so the defaults for this addon are 23 self and 17 other. " ..
					"Be aware if you make them too big then not many auras will fit on the frame. " ..
					"If you go larger than 23 then only 3 auras per row will fit instead of 4.",
			fontSize = "medium",
			order = 6,
		},
	},
}


--Load option defaults
LSA.optionDefaults = {
	global = {
		enable = true,
		selfSize = 23,
		otherSize = 17,
	},
}

--Enable resizing auras.
function LSA:setEnable(info, value)
	self.db.global.enable = value;
	LSA:updateVars();
	if (TargetFrame) then
		TargetFrame_UpdateAuras(TargetFrame);
	end
end

function LSA:getEnable(info)
	return self.db.global.enable;
end

--Self size.
function LSA:setSelf(info, value)
	self.db.global.selfSize = value;
	LSA:updateVars();
end

function LSA:getSelf(info)
	return self.db.global.selfSize;
end

--Other size.
function LSA:setOther(info, value)
	self.db.global.otherSize = value;
	LSA:updateVars();
end

function LSA:getOther(info)
	return self.db.global.otherSize;
end
