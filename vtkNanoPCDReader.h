#pragma once

#include "polydatacore_global.h"
#include "vtkPolyDataAlgorithm.h" //superclass

class POLYDATACORE_EXPORT vtkNanoPCDReader : public vtkPolyDataAlgorithm
{
public:
	vtkTypeMacro(vtkNanoPCDReader, vtkPolyDataAlgorithm);
	static vtkNanoPCDReader *New();
	void PrintSelf(ostream& os, vtkIndent indent);

	vtkSetStringMacro(FileName);
	vtkGetStringMacro(FileName);

protected:
	vtkNanoPCDReader(void);
	~vtkNanoPCDReader(void);
	int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

protected:
	char*           FileName;

private:
	vtkNanoPCDReader(const vtkNanoPCDReader&); // Not implemented
	void operator=(const vtkNanoPCDReader&);    // Not implemented
};

