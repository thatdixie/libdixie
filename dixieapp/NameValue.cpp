#include "NameValue.h"

void NameValue::setName(string n)
{
    name = n;
}

void NameValue::setValue(string v)
{
    value = v;
}


string NameValue::getValue()
{
    return(value);
}

string NameValue::getName()
{
    return(name);
}

int NameValue::intValue()
{
    return(atoi(value.c_str()));    
}

char NameValue::charValue()
{
    return(value[0]);
}


bool NameValue::boolValue()
{
    if((value=="true")
    || (value=="TRUE")
    || (value=="yes" )    
       || (value=="YES" ))
       return (true);
    else
       return (false);
}

long NameValue::longValue()
{
    return(atol(value.c_str()));
}

short NameValue::shortValue()
{
    return(atoi(value.c_str()));
}

float NameValue::floatValue()
{
    return (atof(value.c_str()));
}

double NameValue::doubleValue()
{
    return (atof(value.c_str()));    
}
    

NameValue::NameValue()
{
    
}

NameValue::NameValue(string n, string v)
{
    setName(n);
    setValue(v);
}
