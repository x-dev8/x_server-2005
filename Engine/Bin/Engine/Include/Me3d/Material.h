#pragma once
#include "Me3d/Me3d.h"
#include <typeinfo>
#include <cassert>
#include "utility.h"

namespace graphics
{
    class Shader;

    /** T类型值的shader参数集合接口。
    */
    struct IShaderParameters
    {
    public:
        virtual bool hasValue() = 0;
        virtual void begin() = 0;
        virtual void next() = 0;
        virtual const std::string& key() const = 0;
        virtual const void* value() const = 0;
        virtual unsigned int valueBytes() const = 0;
        virtual const std::type_info & type() const = 0;
    };

    /** T类型值的shader参数集合实现类。
    */
    template< typename T >
    struct ShaderParameters : IShaderParameters, public MeCommonAllocObj<ShaderParameters<T> >
	{
    public:
        typedef std::map< std::string, T > ValueType;
        ValueType values;

        virtual bool hasValue()
        {
            return _currIt != values.end();
        }

        virtual void begin()
        {
            _currIt = values.begin();
        }

        virtual void next()
        {
            ++_currIt;
        }

        virtual const std::string& key() const
        {
            return _currIt->first;
        }

        virtual const void* value() const
        {
            return static_cast<const void*>(&_currIt->second);
        }

        virtual unsigned int valueBytes() const
        {
            return sizeof(T);
        }

        virtual const std::type_info & type() const
        {
            return typeid( T );
        }

    protected:
        typename ValueType::const_iterator _currIt;
        typename ValueType::const_iterator _nextIt;
    };

    /** vector类型shader参数。
    */
    template< typename T >
    struct ShaderVectorParameters : ShaderParameters< std::vector< T > >
    {
    public:
        virtual const void* value() const
        {
            return static_cast<const void*>(&_currIt->second[0]);
        }

        virtual unsigned int valueBytes() const
        {
            return static_cast<unsigned int>( sizeof(T) * _currIt->second.size() );
        }
    };

    typedef std::vector< IShaderParameters* > ShaderParametersList;

    /** shader参数类型比较函数。
    */
    template< typename T >
    struct ShaderParametersTypeCompare
    {
        bool operator() ( const IShaderParameters* v ) const
        {
            return v->type() == typeid( T );
        }
    };

	class Material : public MeCommonAllocObj<Material>
    {
    public:
        /** 构造函数。
        */
        Material();

        /** 构造函数。
        */
        Material( const std::string& name );

        /** 析构函数。
        */
        virtual ~Material();

        /** 得到Material实例名称。
        */
        const std::string& getName() const { return _name; }

        /** 设置shader参数。
        @param name shader参数名。
        @param value shader参数值。
        */
        template< typename ValueType >
        void setParameter( const std::string& name, const ValueType& value )
        {
            ShaderParametersList::iterator it = std::find_if( _parametersList.begin(), _parametersList.end(), ShaderParametersTypeCompare<ValueType>() );
            ShaderParameters< ValueType >* params = NULL;
            if ( it == _parametersList.end() )
            {
                params = MeNew ShaderParameters< ValueType >();
                _parametersList.push_back( params );
            }
            else
            {
                params = static_cast< ShaderParameters< ValueType >* >( *it );
            }

            params->values[name] = value;
        }

        /** 设置shader参数。
        @param name shader参数名。
        @param value shader参数值。
        */
        template< typename ValueType >
        void setParameter( const std::string& name, const std::vector<ValueType>& value )
        {
            ShaderParametersList::iterator it = std::find_if( _parametersList.begin(), _parametersList.end(), ShaderParametersTypeCompare<std::vector<ValueType>>() );
            ShaderVectorParameters< ValueType >* params = NULL;
            if ( it == _parametersList.end() )
            {
                params = MeNew ShaderVectorParameters< ValueType >();
                _parametersList.push_back( params );
            }
            else
            {
                params = static_cast< ShaderVectorParameters< ValueType >* >( *it );
            }

            params->values[name] = value;
        }

        /** 设置shader参数。
        @param name shader参数名。
        @param value shader参数值。
        */
        void setParameter( const std::string& name, const D3DXMATRIXA16& value )
        {
            setParameter( name, static_cast<D3DXMATRIX>(value) );
        }

        /** 设置shader参数。
        @param name shader参数名。
        @param value shader参数值。
        */
        void setParameter( const std::string& name, double value )
        {
            setParameter( name, static_cast<float>(value) );
        }

        /** 得到shader参数值。Exception: std::exception.
        @param name shader参数名。
        */
        template< typename ValueType >
        const ValueType& getParameter( const std::string& name ) const
        {
            ShaderParametersList::const_iterator it = std::find_if(
                _parametersList.begin(), _parametersList.end(), ShaderParametersTypeCompare<ValueType>() );
            if ( it == _parametersList.end() )
            {
                assert( 0 && "不能设置该类型的参数！" );
                STD_ThrowException( "不能设置该类型的参数！" );
            }

            ShaderParameters< ValueType >* params = static_cast< ShaderParameters< ValueType >* >( *it );
            assert( params->values.find( name ) != params->values.end() && "不存在该参数！" );
            return params->values[name];
        }

        /** 得到shader参数值指针。
        @param name shader参数名。
        */
        template< typename ValueType >
        const ValueType* getParameterPtr( const std::string& name ) const
        {
            ShaderParametersList::const_iterator it = std::find_if(
                _parametersList.begin(), _parametersList.end(), ShaderParametersTypeCompare<ValueType>() );
            if ( it != _parametersList.end() )
            {
                ShaderParameters< ValueType >* params = static_cast< ShaderParameters< ValueType >* >( *it );
                ShaderParameters< ValueType >::ValueType::const_iterator itvalue = params->values.find( name );
                if ( itvalue != params->values.end() )
                    return &(itvalue->second);
            }
            return NULL;
        }

        /** 得到所有的shader参数。
        */
        const ShaderParametersList& getShaderParametersList() const { return _parametersList; }

        /** 通过Shader实例名来设置Shader。Exception: std::exception.
        @param shaderName Shader实例名。
        */
        Shader* setShader( const std::string& shaderName );

        /** 得到Shader实例。
        */
        Shader* getShader();

        /** 设置Shader使用的Technique。
        */
        void setTechnique( const std::string& technique ) { _technique = technique; }

        /** 得到Shader使用的Technique。
        */
        const std::string& getTechnique() const { return _technique; }

    public:
        std::string          _name;
        std::string          _technique;
        ShaderParametersList _parametersList;
        Shader*              _pShader;
    };
}