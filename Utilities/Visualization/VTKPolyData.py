#!/usr/bin/env python

"""Render VTK Polydata and view or save PNG or save WebGL.

When an output PNG or WebGL file is not specified, an interactive windows is
displayed.  To get the camera position from the interactive window, press the
"c" key.
"""

import argparse
import sys

import vtk


def three_floats(value):
    values = value[1:-1].split(',')
    if len(values) != 3:
        raise argparse.ArgumentError
    return map(float, values)


def two_floats(value):
    values = value[1:-1].split(',')
    if len(values) != 2:
        raise argparse.ArgumentError
    return map(float, values)
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('inputFile', help='.vtk PolyData input')
parser.add_argument('--position', help='Camera Position',
                    type=three_floats, metavar=('x,y,z'))
parser.add_argument('--focal-point', help='Camera FocalPoint',
                    type=three_floats, metavar=('x,y,z'))
parser.add_argument('--view-up', help='Camera ViewUp',
                    type=three_floats, metavar=('x,y,z'))
parser.add_argument('--size', help='Window size in pixels',
                    type=int, metavar=('width', 'height'), nargs=2)
parser.add_argument('--clipping-range', help='Window size in pixels',
                    type=two_floats, metavar=('near,far'))
parser.add_argument('--png', help='Output PNG file',
                    metavar='file.png')
parser.add_argument('--webgl', help='File prefix for WebGL output',
                    metavar='webglFilePrefix')
args = parser.parse_args()

reader = vtk.vtkPolyDataReader()
reader.SetFileName(args.inputFile)

frame_mapper = vtk.vtkDataSetMapper()
frame_mapper.SetInputConnection(reader.GetOutputPort())
frame_actor = vtk.vtkActor()
frame_actor.SetMapper(frame_mapper)
prop = frame_actor.GetProperty()
prop.SetRepresentationToWireframe()
prop.SetColor(0.0, 0.0, 1.0)

surface_mapper = vtk.vtkDataSetMapper()
surface_mapper.SetInputConnection(reader.GetOutputPort())
surface_actor = vtk.vtkActor()
surface_actor.SetMapper(surface_mapper)
prop = surface_actor.GetProperty()
prop.SetRepresentationToSurface()

render_window = vtk.vtkRenderWindow()
renderer = vtk.vtkRenderer()
renderer.SetBackground(0.33, 0.33, 0.45)
render_window.AddRenderer(renderer)
render_window.SetSize(640, 480)
if args.size:
    render_window.SetSize(args.size)

render_window_interactor = vtk.vtkRenderWindowInteractor()
render_window_interactor.SetRenderWindow(render_window)

renderer.AddActor(frame_actor)
renderer.AddActor(surface_actor)
render_window.Render()

camera = renderer.GetActiveCamera()


def print_camera_position(interactor, event):
    def cmd_line_friendly(xyz):
        return '[{0:+8.4e},{1:+8.4e},{2:+8.4e}]'.format(*xyz)

    def cmd_line_friendly2(clip_range):
        return '[{0:+8.4e},{1:+8.4e}]'.format(*clip_range)
    if interactor.GetKeySym() == 'c':
        print('\nPosition:    ' + cmd_line_friendly(camera.GetPosition()))
        print('FocalPoint:   ' + cmd_line_friendly(camera.GetFocalPoint()))
        print('ViewUp:       ' + cmd_line_friendly(camera.GetViewUp()))
        print('ClippingRange:' + cmd_line_friendly2(camera.GetClippingRange()))
        sys.stdout.write('\n--position ')
        sys.stdout.write(cmd_line_friendly(camera.GetPosition()))
        sys.stdout.write(' --focal-point ')
        sys.stdout.write(cmd_line_friendly(camera.GetFocalPoint()))
        sys.stdout.write(' --view-up ')
        sys.stdout.write(cmd_line_friendly(camera.GetViewUp()))
        sys.stdout.write(' --clipping-range ')
        sys.stdout.write(cmd_line_friendly2(camera.GetClippingRange()))
        sys.stdout.write('\n')
        sys.stdout.flush()
render_window_interactor.AddObserver('KeyPressEvent', print_camera_position)

if args.position:
    camera.SetPosition(args.position)
if args.focal_point:
    camera.SetFocalPoint(args.focal_point)
if args.view_up:
    camera.SetViewUp(args.view_up)
if args.clipping_range:
    camera.SetClippingRange(args.clipping_range)

if args.png:
    window_to_image = vtk.vtkWindowToImageFilter()
    window_to_image.SetInput(render_window)
    png_writer = vtk.vtkPNGWriter()
    png_writer.SetInputConnection(window_to_image.GetOutputPort())
    png_writer.SetFileName(args.png)
    png_writer.Write()

if args.webgl:
    webgl_exporter = vtk.vtkPVWebGLExporter()
    webgl_exporter.SetFileName(args.webgl)
    webgl_exporter.SetRenderWindow(render_window)
    webgl_exporter.Update()

if not args.png and not args.webgl:
    render_window_interactor.Start()
