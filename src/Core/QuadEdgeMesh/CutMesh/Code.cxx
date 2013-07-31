#include "itkQuadEdgeMesh.h"
#include "itkQuadEdgeMeshPolygonCell.h"

#include "itkMeshFileReader.h"
#include "itkMeshFileWriter.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
     {
     std::cerr << "Usage: "<< std::endl;
     std::cerr << argv[0];
     std::cerr << " <InputFileName> <OutputFileName>";
     std::cerr << std::endl;
     return EXIT_FAILURE;
     }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const unsigned int Dimension = 3;
  typedef double CoordType;
  typedef itk::QuadEdgeMesh< CoordType, Dimension > MeshType;
  typedef MeshType::Pointer                         MeshPointer;
  typedef MeshType::PointsContainerPointer          MeshPointsContainerPointer;
  typedef MeshType::PointsContainerIterator         MeshPointsContainerIterator;
  typedef MeshType::PointType                       MeshPointType;
  typedef MeshType::PointIdentifier                 MeshPointIdentifier;
  typedef MeshType::CellIdentifier                  MeshCellIdentifier;

  typedef itk::MeshFileReader< MeshType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject& e )
    {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
    }

  MeshPointer mesh = reader->GetOutput();

  MeshPointer output = MeshType::New();

  std::map< MeshPointIdentifier, MeshPointIdentifier > verticesMap;
  std::set< MeshCellIdentifier > facesSet;

  MeshPointsContainerPointer points = mesh->GetPoints();

  MeshPointsContainerIterator pIt   = points->Begin();
  MeshPointsContainerIterator pEnd  = points->End();

  while( pIt != pEnd )
  {
    MeshPointType p = pIt->Value();

    if( ( p[2] < 0. ) )
      {
      // here you do not want to use operator = to copy the coordinates from the
      // input mesh to the output one. Indeed the operator = does not only copy
      // the coordinates, but also the pointer to first QuadEdge of the 0-ring,
      // and it would be wrong.
      MeshPointType q;
      q.CastFrom( p );

      verticesMap[ pIt->Index() ] = output->AddPoint( q );

      // iterate on the 0-ring (vertex neighbors)
      MeshType::QEType* qe = p.GetEdge();
      MeshType::QEType* temp = qe;
      do
        {
        // insert the corresponding faces into std::set
        facesSet.insert( temp->GetLeft() );

        temp = temp->GetOnext();
        } while( qe != temp );
      }
    ++pIt;
  }

  MeshType::CellsContainerPointer cells = mesh->GetCells();

  typedef itk::QuadEdgeMeshPolygonCell< MeshType::CellType > PolygonType;

  // iterate on the faces to be added into resulting mesh
  for( std::set< MeshType::CellIdentifier >::iterator fIt = facesSet.begin();
       fIt != facesSet.end();
       ++fIt )
    {
    PolygonType* face = dynamic_cast< PolygonType* >( cells->ElementAt( *fIt ) );
    MeshType::PointIdentifier id[3];

    if( face )
      {
      MeshType::QEType *qe = face->GetEdgeRingEntry();
      MeshType::QEType *temp = qe;

      unsigned int k = 0;

      // iterate on the vertices of a given face
      do
        {
        // add the corresponding vertex into the output mesh if it has not been added yet
        if( verticesMap.find( temp->GetOrigin() ) == verticesMap.end() )
          {
          MeshType::PointType p = mesh->GetPoint( temp->GetOrigin() );

          MeshType::PointType q;
          q.CastFrom( p );

          verticesMap[ temp->GetOrigin() ] = output->AddPoint( q );
          }
        id[ k++ ] = verticesMap[ temp->GetOrigin() ];

        temp = temp->GetLnext();
        } while( qe != temp );

      // add the corresponding face into the output mesh
      output->AddFaceTriangle( id[0], id[1], id[2] );
      }
    }

  // save the corresponding mesh
  typedef itk::MeshFileWriter< MeshType > MeshWriterType;
  MeshWriterType::Pointer writer = MeshWriterType::New();
  writer->SetInput( output );
  writer->SetFileName( outputFileName );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject& e )
    {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
