#include "Me3d/Material.h"
#include "Me3d/Shader.h"
#include "Me3d/ShaderManager.h"

namespace graphics
{
    Material::Material() : _pShader( NULL )
    {
    }

    Material::Material( const std::string& name ) : _name( name ),
         _pShader( NULL )
    {
    }

    Material::~Material()
    {
        ShaderParametersList::iterator it, end = _parametersList.end();
        for ( it = _parametersList.begin(); it != end; ++it )
        {
            delete *it;
        }
        _parametersList.clear();
    }

    Shader* Material::setShader(const std::string& shaderName)
    {
        _pShader = ShaderManager::instance()->getShader( shaderName );
        return _pShader;
    }

    Shader* Material::getShader()
    {
        return _pShader;
    }
}