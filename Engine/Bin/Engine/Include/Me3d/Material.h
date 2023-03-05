#pragma once
#include "Me3d/Me3d.h"
#include <typeinfo>
#include <cassert>
#include "utility.h"

namespace graphics
{
    class Shader;

    /** T����ֵ��shader�������Ͻӿڡ�
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

    /** T����ֵ��shader��������ʵ���ࡣ
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

    /** vector����shader������
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

    /** shader�������ͱȽϺ�����
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
        /** ���캯����
        */
        Material();

        /** ���캯����
        */
        Material( const std::string& name );

        /** ����������
        */
        virtual ~Material();

        /** �õ�Materialʵ�����ơ�
        */
        const std::string& getName() const { return _name; }

        /** ����shader������
        @param name shader��������
        @param value shader����ֵ��
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

        /** ����shader������
        @param name shader��������
        @param value shader����ֵ��
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

        /** ����shader������
        @param name shader��������
        @param value shader����ֵ��
        */
        void setParameter( const std::string& name, const D3DXMATRIXA16& value )
        {
            setParameter( name, static_cast<D3DXMATRIX>(value) );
        }

        /** ����shader������
        @param name shader��������
        @param value shader����ֵ��
        */
        void setParameter( const std::string& name, double value )
        {
            setParameter( name, static_cast<float>(value) );
        }

        /** �õ�shader����ֵ��Exception: std::exception.
        @param name shader��������
        */
        template< typename ValueType >
        const ValueType& getParameter( const std::string& name ) const
        {
            ShaderParametersList::const_iterator it = std::find_if(
                _parametersList.begin(), _parametersList.end(), ShaderParametersTypeCompare<ValueType>() );
            if ( it == _parametersList.end() )
            {
                assert( 0 && "�������ø����͵Ĳ�����" );
                STD_ThrowException( "�������ø����͵Ĳ�����" );
            }

            ShaderParameters< ValueType >* params = static_cast< ShaderParameters< ValueType >* >( *it );
            assert( params->values.find( name ) != params->values.end() && "�����ڸò�����" );
            return params->values[name];
        }

        /** �õ�shader����ֵָ�롣
        @param name shader��������
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

        /** �õ����е�shader������
        */
        const ShaderParametersList& getShaderParametersList() const { return _parametersList; }

        /** ͨ��Shaderʵ����������Shader��Exception: std::exception.
        @param shaderName Shaderʵ������
        */
        Shader* setShader( const std::string& shaderName );

        /** �õ�Shaderʵ����
        */
        Shader* getShader();

        /** ����Shaderʹ�õ�Technique��
        */
        void setTechnique( const std::string& technique ) { _technique = technique; }

        /** �õ�Shaderʹ�õ�Technique��
        */
        const std::string& getTechnique() const { return _technique; }

    public:
        std::string          _name;
        std::string          _technique;
        ShaderParametersList _parametersList;
        Shader*              _pShader;
    };
}