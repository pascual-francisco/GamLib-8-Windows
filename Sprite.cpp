#include "Sprite.h"

Sprite::Sprite(GLuint spriteid, GLuint pte, GLuint pge, GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat tix, GLfloat tiy, GLuint tsx, GLuint tsy, GLuint cda, GLuint adi, GLint fie, GLint lae, GLint ace, GLfloat frt, GLuint ste)
{	
	init(spriteid, pte, pge, s, t, p, q, tix, tiy, tsx, tsy, cda, adi, fie, lae, ace, frt, ste);
}

Sprite::~Sprite()
{


	if (ptrAnimation != nullptr)
		delete ptrAnimation;
}

Sprite::Sprite(const Sprite &object)
{
	if (&object != this)
	{
			spriteID = object.spriteID;
			active = object.active;
			texturePalette = object.texturePalette;
			palettePage = object.palettePage;
			positionOffset = object.positionOffset;
			textureOffset = object.textureOffset;
			ptrAnimation = object.ptrAnimation;			
			tileIndex = object.tileIndex;			
			transformation.translate = object.transformation.translate;
			transformation.pivot = object.transformation.pivot;
			transformation.rotate = object.transformation.rotate;
			transformation.scale = object.transformation.scale;
			collisionData = object.collisionData;
			animationDirection = object.animationDirection;
			tileSeparation = object.tileSeparation;			
			vertexColor[0] = object.vertexColor[0];
			vertexColor[1] = object.vertexColor[1];
			vertexColor[2] = object.vertexColor[2];
			vertexColor[3] = object.vertexColor[3];		
			secondaryColor[0] = object.secondaryColor[0];
			secondaryColor[1] = object.secondaryColor[1];
			secondaryColor[2] = object.secondaryColor[2];
			secondaryColor[3] = object.secondaryColor[3];

	}
}

void Sprite::init(GLuint spriteid, GLuint pte, GLuint pge, GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat tix, GLfloat tiy, GLuint tsx, GLuint tsy, GLuint cda, GLuint adi, GLint ff, GLint lf, GLint af, GLfloat ft, GLuint as)
{

	spriteID = spriteid;
	active = true;
	texturePalette = pte;
	palettePage = pge;
	positionOffset = vec2(0.0f, 0.0f);
	textureOffset = vec4(s, t, p, q);	
	ptrAnimation = new Animation(ff, lf, af, ft, as);
	tileIndex = vec2(tix, tiy);		
	transformation.translate = vec3(0.0f, 0.0f, 0.0f);
	transformation.pivot = vec3(0.0f, 0.0f, 0.0f);
	transformation.rotate = vec3(0.0f, 0.0f, 0.0f);
	transformation.scale = vec3(1.0f, 1.0f, 1.0f);
	collisionData = cda;
	tileSeparation = vec2(tsx, tsy);
	animationDirection = adi;

	for (uint i = 0; i < 4; i++)
	{
		vertexColor[i].r = 0.0f;
		vertexColor[i].g = 0.0f;
		vertexColor[i].b = 0.0f;
		secondaryColor[i].r = 0.0f;
		secondaryColor[i].g = 0.0f;
		secondaryColor[i].b = 0.0f;
	}

	for (uint i = 0; i < 4; i++)
		vertexColor[i].a = 1.0f;	
}

const Sprite &Sprite::operator=(const Sprite &object)
{
	if (&object != this)
	{
		spriteID = object.spriteID;
		active = object.active;
		texturePalette = object.texturePalette;
		palettePage = object.palettePage;
		positionOffset = object.positionOffset;
		textureOffset = object.textureOffset;
		ptrAnimation = object.ptrAnimation;		
		tileIndex = object.tileIndex;		
		transformation.translate = object.transformation.translate;
		transformation.pivot = object.transformation.pivot;
		transformation.rotate = object.transformation.rotate;
		transformation.scale = object.transformation.scale;
		collisionData = object.collisionData;
		animationDirection = object.animationDirection;
		tileSeparation = object.tileSeparation;
		vertexColor[0] = object.vertexColor[0];
		vertexColor[1] = object.vertexColor[1];
		vertexColor[2] = object.vertexColor[2];
		vertexColor[3] = object.vertexColor[3];
		secondaryColor[0] = object.secondaryColor[0];
		secondaryColor[1] = object.secondaryColor[1];
		secondaryColor[2] = object.secondaryColor[2];
		secondaryColor[3] = object.secondaryColor[3];

	}
	return *this;
}

bool Sprite::operator ==(const Sprite &object) const
{
	if (&object != this)
	{
		if (
			spriteID == object.spriteID &&
			active == object.active &&
			texturePalette == object.texturePalette &&
			palettePage == object.palettePage &&
			positionOffset == object.positionOffset &&
			textureOffset == object.textureOffset &&
			ptrAnimation == object.ptrAnimation &&			
			tileIndex == object.tileIndex &&			
			transformation.translate == object.transformation.translate &&
			transformation.pivot == object.transformation.pivot &&
			transformation.rotate == object.transformation.rotate &&
			transformation.scale == object.transformation.scale &&
			collisionData == object.collisionData &&
			animationDirection == object.animationDirection &&
			tileSeparation == object.tileSeparation  &&
			vertexColor == object.vertexColor &&
			secondaryColor == object.secondaryColor 
			

			)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Sprite::operator <(const Sprite &object) const
{
	if (ptrAnimation->lastFrame < object.ptrAnimation->lastFrame)
			return true;
		else
			return false;
}

bool Sprite::operator >(const Sprite &object) const
{
	if (ptrAnimation->lastFrame > object.ptrAnimation->lastFrame)
		return true;
	else
		return false;
}

bool Sprite::operator*( Sprite &object)
{
	SDL_Rect a, b;
	a.x = transformation.translate.x;
	a.y = transformation.translate.y;
	a.w = textureOffset.p;
	a.h = textureOffset.q;
	b.x = object.transformation.translate.x;
	b.y = object.transformation.translate.y;
	b.w = object.textureOffset.p;
	b.h = object.textureOffset.q;

	if (SDL_HasIntersection(&a, &b))
	{
		return true;

	}
	else
	{
		return false;
	}
}

void Sprite::update()
{
	if (ptrAnimation != nullptr)
	{
		ptrAnimation->update();
	}
}

void Sprite::print() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Sprite Info: " << endl;
	cout << "Sprite ID = " <<spriteID<<endl;	
	cout << "Active = " << spriteID << endl;
	cout << "Texture Palette = " << texturePalette << endl;
	cout << "Palette Page  = " << palettePage << endl;
	cout << "Texture Offset = [" << textureOffset.s << ", " << textureOffset.t << ", " << textureOffset.p << ", " << textureOffset.q << "]" << endl;
	cout << "Tile Index = [" << tileIndex.x << ", " << tileIndex.y << "]" << endl;	
	cout << "Tile Separation = [" << tileSeparation.x << ", " << tileSeparation.y << "]" << endl;
	cout << "Animation Direction = " << animationDirection << endl;
	cout << "Collision Data = " << collisionData << endl;
	transformation.print();
	cout << "Vertex Color [0] = [ " << vertexColor[0].r << ", " << vertexColor[0].g << ", " << vertexColor[0].b << ", " << vertexColor[0].a << " ]" << endl;
	cout << "Vertex Color [1] = [ " << vertexColor[1].r << ", " << vertexColor[1].g << ", " << vertexColor[1].b << ", " << vertexColor[1].a << " ]" << endl;
	cout << "Vertex Color [2] = [ " << vertexColor[2].r << ", " << vertexColor[2].g << ", " << vertexColor[2].b << ", " << vertexColor[2].a << " ]" << endl;
	cout << "Vertex Color [3] = [ " << vertexColor[3].r << ", " << vertexColor[3].g << ", " << vertexColor[3].b << ", " << vertexColor[3].a << " ]" << endl;
	cout << "Secondary Color [0] = [ " << secondaryColor[0].r << ", " << secondaryColor[0].g << ", " << secondaryColor[0].b << ", " << secondaryColor[0].a << " ]" << endl;
	cout << "Secondary Color [1] = [ " << secondaryColor[1].r << ", " << secondaryColor[1].g << ", " << secondaryColor[1].b << ", " << secondaryColor[1].a << " ]" << endl;
	cout << "Secondary Color [2] = [ " << secondaryColor[2].r << ", " << secondaryColor[2].g << ", " << secondaryColor[2].b << ", " << secondaryColor[2].a << " ]" << endl;
	cout << "Secondary Color [3] = [ " << secondaryColor[3].r << ", " << secondaryColor[3].g << ", " << secondaryColor[3].b << ", " << secondaryColor[3].a << " ]" << endl;


	if (ptrAnimation != nullptr)
	{
		ptrAnimation->print();
	}
	else
	{
		cout << "Animation is empty" << endl;
	}
	cout << "Position Offset = [ " << positionOffset.x << " , " << positionOffset.y << " ]" << endl;
	cout << "Sprite Info: " << endl;
	cout << "******************************************************************************************************************************************************************************" << endl;
}