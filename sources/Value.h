#pragma once

#include "Nodable.h"    // for constants and forward declarations
#include <string>

namespace Nodable{

	enum Type_{
		Type_Unknown,
		Type_Boolean,
		Type_Number,
		Type_String,
		Type_COUNT
	};
	
	enum Visibility_{
		Visibility_Public    = 0,
		Visibility_Protected = 1,
		Visibility_Private   = 2,
		Visibility_Default   = Visibility_Public
	};

	/* 
		This class is variant implementation
	*/

	class Value{
	public:
		Value();
		~Value();

		bool        isSet            ()const;	
		bool        isType           (Type_ _type)const;

		void  		setName			 (const char* _name){name = _name;}
		void        setValue         (const Value&);
		void        setValue         (std::string);
		void        setValue         (const char*);
		void        setValue         (double);
		void        setValue         (bool);
		
		void        setType          (Type_ _type){type = _type;}
		void        setVisibility    (Visibility_ _v){visibility = _v;}

		const std::string& getName   ()const{return name;}
		Type_       getType          ()const;
		std::string getTypeAsString  ()const;

		bool        getValueAsBoolean()const;
		double      getValueAsNumber ()const;
		std::string getValueAsString ()const;

		Visibility_ getVisibility    ()const{ return visibility;}
	private:
		std::string name 		= "Unknown";
		void*       data 		= NULL;
		Type_       type 		= Type_Unknown;
		Visibility_ visibility 	= Visibility_Default;
	};
}