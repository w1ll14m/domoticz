//-----------------------------------------------------------------------------
//
//	CentralScene.h
//
//	Implementation of the Z-Wave COMMAND_CLASS_CENTRAL_SCENE
//
//	Copyright (c) 2012 Greg Satz <satz@iranger.com>
//
//	SOFTWARE NOTICE AND LICENSE
//
//	This file is part of OpenZWave.
//
//	OpenZWave is free software: you can redistribute it and/or modify
//	it under the terms of the GNU Lesser General Public License as published
//	by the Free Software Foundation, either version 3 of the License,
//	or (at your option) any later version.
//
//	OpenZWave is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU Lesser General Public License for more details.
//
//	You should have received a copy of the GNU Lesser General Public License
//	along with OpenZWave.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

#ifndef _CentralScene_H
#define _CentralScene_H

#include "command_classes/CommandClass.h"
#include "TimerThread.h"

namespace OpenZWave
{
	class ValueByte;

	/** \brief Implements COMMAND_CLASS_CENTRAL_SCENE (0x5B), a Z-Wave device command class.
	 *  \ingroup CommandClass
	 */
	class CentralScene: public CommandClass, private Timer
	{
	public:
		static CommandClass* Create( uint32 const _homeId, uint8 const _nodeId ){ return new CentralScene( _homeId, _nodeId ); }
		virtual ~CentralScene(){}

		/** \brief Get command class ID (1 byte) identifying this command class. */
		static uint8 const StaticGetCommandClassId(){ return 0x5B; }
		/** \brief Get a string containing the name of this command class. */
		static string const StaticGetCommandClassName(){ return "COMMAND_CLASS_CENTRAL_SCENE"; }

		// From CommandClass
		/** \brief Get command class ID (1 byte) identifying this command class. (Inherited from CommandClass) */
		virtual uint8 const GetCommandClassId() const override{ return StaticGetCommandClassId(); }
		/** \brief Get a string containing the name of this command class. (Inherited from CommandClass) */
		virtual string const GetCommandClassName() const override{ return StaticGetCommandClassName(); }
		virtual uint8 GetMaxVersion() override { return 3; }
		/** \brief Handle a response to a message associated with this command class. (Inherited from CommandClass) */
		virtual bool HandleMsg( uint8 const* _data, uint32 const _length, uint32 const _instance = 1 ) override;
		bool RequestState( uint32 const _requestFlags, uint8 const _instance, Driver::MsgQueue const _queue ) override;
		bool RequestValue( uint32 const _requestFlags, uint16 const _what, uint8 const _instance, Driver::MsgQueue const _queue ) override;
		bool SetValue( Value const& _value) override;
protected:
		/** \brief Create Default Vars for this CC */
		void CreateVars( uint8 const _instance ) override;

	private:
		/**
		 * Creates the ValueIDs for the keyAttributes
		 * @param identical
		 * @param keyAttributes
		 * @param sceneNumber
		 * @return
		 */
		void createSupportedKeyAttributesValues(uint8 keyAttributes, uint8 sceneNumber, uint8 instance);
		void ClearScene(uint32 sceneID);
		CentralScene( uint32 const _homeId, uint8 const _nodeId );
		bool m_slowrefresh;
		uint8 m_sequence;
		std::map<uint32, uint32> m_TimersSet;
	};

} // namespace OpenZWave

#endif
